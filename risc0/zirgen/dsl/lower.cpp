// Copyright 2024 RISC Zero, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "lower.h"
#include "zirgen/Dialect/ZHL/IR/ZHL.h"

#include <map>

#include "mlir/IR/Builders.h"
#include "mlir/IR/Verifier.h"
#include "llvm/ADT/TypeSwitch.h"
#include "llvm/Support/SourceMgr.h"

namespace zirgen {
namespace dsl {

namespace {

using namespace zirgen::Zhl;
using mlir::MLIRContext;
typedef llvm::SmallVector<mlir::Value, 4> ValueVector;

enum class Source {
  Definition,
  Declaration,
  Global,
  Map,
  TypeParam,
  ConstructorParam,
  Component,
};

struct Def {
  mlir::Value value;
  Source source;
  mlir::Location location;
};

class SymbolTable {
public:
  SymbolTable() {}
  SymbolTable(const SymbolTable& chain) : chain(&chain) {}
  void define(llvm::StringRef n, Def d) {
    // Look for an existing definition of this name. If we find one, it must
    // have come from a Declaration statement, and the statement providing the
    // replacement must be a Definition; any other form of re-definition is
    // an error, which we must report to the user.

    auto prevDef = lookup(n);
    if (prevDef) {
      if ((d.source != Source::Definition || prevDef->source != Source::Declaration)
          // Always allow shadowing constructor parameters, since it's common to just save them as
          // registers.
          && prevDef->source != Source::ConstructorParam) {
        auto diag = mlir::emitError(d.location);
        diag << "Conflicting definition of `" << n << "`";
        diag.attachNote(prevDef->location) << "see previous definition";
      }

      // If it's declared locally, remove the declaration so it can be replaced with the definition.
      auto iter = defs.find(n);
      if (iter != defs.end()) {
        defs.erase(iter);
      }
    }
    defs.insert({n, d});
  }
  std::optional<Def> lookup(llvm::StringRef n) const {
    // Search the chain of nested scopes for a definition
    auto d = local(n);
    return d ? d : (chain ? chain->lookup(n) : std::nullopt);
  }
  std::optional<Def> local(llvm::StringRef n) const {
    // Find a definition if it exists in this scope
    auto iter = defs.find(n);
    if (iter != defs.end()) {
      return iter->second;
    }
    return std::nullopt;
  }

private:
  std::map<llvm::StringRef, Def> defs;
  const SymbolTable* chain = nullptr;
};

struct Impl {
  Impl(MLIRContext& ctx, const llvm::SourceMgr& sourceManager);
  mlir::ModuleOp gen(ast::Module*, SymbolTable&);

private:
  mlir::Value gen(ast::Expression*, SymbolTable&);
  ValueVector gen(ast::Expression::ArrayRef, SymbolTable&);
  void gen(ast::Statement*, SymbolTable&);
  void gen(ast::Component*, SymbolTable&);
  void genBlockBody(ast::Block*, SymbolTable&);

  template <typename T> mlir::Location loc(T*);
  template <typename T> mlir::Location loc(const std::shared_ptr<T>& x);

  MLIRContext& ctx;
  const llvm::SourceMgr& sourceManager;
  mlir::OpBuilder builder;
  mlir::Type exprType;
  mlir::StringAttr curComponent;
};

Impl::Impl(MLIRContext& ctx, const llvm::SourceMgr& mgr)
    : ctx(ctx), sourceManager(mgr), builder(&ctx) {
  exprType = ExprType::get(&ctx);
}

mlir::ModuleOp Impl::gen(ast::Module* m, SymbolTable& symbols) {
  auto loc = builder.getUnknownLoc();
  auto out = mlir::ModuleOp::create(loc);
  builder.setInsertionPointToEnd(&out.getBodyRegion().front());
  for (auto& c : m->getBody()) {
    curComponent = {};
    gen(c.get(), symbols);
  }
  return out;
}

mlir::Value Impl::gen(ast::Expression* e, SymbolTable& symbols) {
  assert(e);
  return llvm::TypeSwitch<ast::Expression*, mlir::Value>(e)
      .Case<ast::Literal>([&](ast::Literal* e) -> mlir::Value {
        uint64_t value = e->getValue();
        return builder.create<LiteralOp>(loc(e), value);
      })
      .Case<ast::StringLiteral>([&](ast::StringLiteral* e) -> mlir::Value {
        mlir::StringAttr str = builder.getStringAttr(e->getValue());
        return builder.create<StringOp>(loc(e), str);
      })
      .Case<ast::Ident>([&](ast::Ident* e) -> mlir::Value {
        llvm::StringRef name = e->getName();
        if (auto def = symbols.lookup(name)) {
          switch (def->source) {
          case Source::Declaration: {
            auto diag = mlir::emitError(loc(e));
            diag << "Cannot use undefined value of symbol `" << name << "`";
            diag.attachNote(def->location) << "declared here";
            // Return dummy value so downstream op builders don't fail
            return builder.create<LiteralOp>(loc(e), 0);
          } break;
          case Source::Component:
            // Return a GlobalOp for all component name references.
            break;
          default:
            return def->value;
          }
        }
        return builder.create<GlobalOp>(loc(e), name);
      })
      .Case<ast::Lookup>([&](ast::Lookup* e) -> mlir::Value {
        mlir::Value component = gen(e->getComponent(), symbols);
        llvm::StringRef member = e->getMember();
        return builder.create<LookupOp>(loc(e), component, member);
      })
      .Case<ast::Subscript>([&](ast::Subscript* e) -> mlir::Value {
        mlir::Value array = gen(e->getArray(), symbols);
        mlir::Value element = gen(e->getElement(), symbols);
        return builder.create<SubscriptOp>(loc(e), array, element);
      })
      .Case<ast::Specialize>([&](ast::Specialize* e) -> mlir::Value {
        mlir::Value type = gen(e->getType(), symbols);
        ValueVector args = gen(e->getArgs(), symbols);
        return builder.create<SpecializeOp>(loc(e), type, args);
      })
      .Case<ast::Construct>([&](ast::Construct* e) -> mlir::Value {
        mlir::Value type = gen(e->getType(), symbols);
        ValueVector args = gen(e->getArgs(), symbols);
        return builder.create<ConstructOp>(loc(e), type, args);
      })
      .Case<ast::Block>([&](ast::Block* e) -> mlir::Value {
        auto op = builder.create<BlockOp>(loc(e));
        builder.createBlock(&op.getInner());
        SymbolTable innerscope(symbols);
        genBlockBody(e, innerscope);
        builder.setInsertionPointAfter(op);
        return op;
      })
      .Case<ast::Map>([&](ast::Map* e) -> mlir::Value {
        mlir::Location sl(loc(e));
        mlir::Value array = gen(e->getArray(), symbols);
        auto op = builder.create<MapOp>(sl, array);
        mlir::Block* inner = builder.createBlock(&op.getFunction());
        SymbolTable innerscope(symbols);
        llvm::StringRef element = e->getElement();
        mlir::BlockArgument arg = inner->addArgument(exprType, sl);
        innerscope.define(element, {arg, Source::Map, sl});
        auto ret = gen(e->getFunction(), innerscope);
        builder.create<SuperOp>(loc(e->getFunction()), ret);
        builder.setInsertionPointAfter(op);
        return op;
      })
      .Case<ast::Reduce>([&](ast::Reduce* e) -> mlir::Value {
        mlir::Value array = gen(e->getArray(), symbols);
        mlir::Value init = gen(e->getInit(), symbols);
        mlir::Value type = gen(e->getType(), symbols);
        return builder.create<ReduceOp>(loc(e), array, init, type);
      })
      .Case<ast::Switch>([&](ast::Switch* e) -> mlir::Value {
        mlir::Value selector = gen(e->getSelector(), symbols);
        size_t numCases = e->getCases().size();
        auto switchOp = builder.create<SwitchOp>(loc(e), selector, numCases);
        if (e->getIsMajor()) {
          switchOp->setAttr("isMajor", builder.getUnitAttr());
        }
        mlir::OpBuilder::InsertionGuard insertionGuard(builder);
        for (size_t i = 0; i < numCases; i++) {
          mlir::Block& block = switchOp.getCases()[i].emplaceBlock();
          builder.setInsertionPointToStart(&block);
          mlir::Value arm = gen(e->getCases()[i].get(), symbols);
          builder.create<SuperOp>(loc(e), arm);
        }
        return switchOp;
      })
      .Case<ast::Range>([&](ast::Range* e) -> mlir::Value {
        mlir::Value start = gen(e->getStart(), symbols);
        mlir::Value end = gen(e->getEnd(), symbols);
        return builder.create<RangeOp>(loc(e), start, end);
      })
      .Case<ast::Back>([&](ast::Back* e) -> mlir::Value {
        mlir::Value distance = gen(e->getDistance(), symbols);
        if (!llvm::isa<ast::Ident>(e->getExpression())) {
          mlir::emitError(loc(e)) << "The target of a back expression must be an identifier";
          // Return dummy value so downstream op builders don't fail
          return builder.create<LiteralOp>(loc(e), 0);
        }
        auto ident = llvm::cast<ast::Ident>(e->getExpression());
        llvm::StringRef name = ident->getName();
        auto def = symbols.lookup(name);
        if (!def) {
          mlir::emitError(loc(e)) << "Back expression is undefined";
          return builder.create<LiteralOp>(loc(e), 0);
        }
        if (!def->value) {
          mlir::emitError(loc(e)) << "Back expression does not have a value";
          return builder.create<LiteralOp>(loc(e), 0);
        }
        return builder.create<BackOp>(loc(e), distance, def->value);
      })
      .Case<ast::ArrayLiteral>([&](ast::ArrayLiteral* e) -> mlir::Value {
        ValueVector elements = gen(e->getElements(), symbols);
        return builder.create<ArrayOp>(loc(e), elements);
      })
      .Default([&](auto) {
        mlir::emitError(loc(e), "Unknown expression type");
        return builder.create<LiteralOp>(loc(e), 0);
      });
}

ValueVector Impl::gen(ast::Expression::ArrayRef vals, SymbolTable& symbols) {
  ValueVector out;
  out.reserve(vals.size());
  for (auto& v : vals) {
    out.push_back(gen(v.get(), symbols));
  }
  return out;
}

void Impl::gen(ast::Statement* s, SymbolTable& symbols) {
  assert(s);
  llvm::TypeSwitch<ast::Statement*>(s)
      .Case<ast::Definition>([&](ast::Definition* s) {
        mlir::Location sl(loc(s));
        llvm::StringRef name = s->getName();
        if (s->getIsGlobal()) {
          auto construct = dynamic_cast<ast::Construct*>(s->getValue());
          if (!construct) {
            mlir::emitError(sl) << "Expecting a global definition to construct a component";
            return;
          }

          mlir::Value type = gen(construct->getType(), symbols);
          ValueVector args = gen(construct->getArgs(), symbols);
          builder.create<ConstructGlobalOp>(sl, name, type, args);

          // Now, make the value of this global available in scope.
          mlir::Value declaration = builder.create<GetGlobalOp>(sl, name, type).getOut();
          symbols.define(name, {declaration, Source::Global, sl});
        } else {
          mlir::Value definition = gen(s->getValue(), symbols);
          // Ensure that there is a declaration for the member. Note that this
          // goes after the definition value so that the declaration is not in
          // scope when that is generated. This makes shadowing possible.
          mlir::Value declaration;
          auto def = symbols.lookup(name);
          if (def && def->source == Source::Declaration) {
            declaration = def->value;
          } else {
            if (def && def->source != Source::ConstructorParam) {
              auto diag = mlir::emitError(sl);
              diag << "Only constructor parameters may be shadowed.";
              diag.attachNote(def->location) << "see previous definition";
            }
            declaration = builder.create<DeclarationOp>(sl, exprType, name, mlir::Value()).getOut();
            symbols.define(name, {declaration, Source::Declaration, sl});
          }
          builder.create<DefinitionOp>(sl, declaration, definition);
          symbols.define(name, {definition, Source::Definition, sl});
        }
      })
      .Case<ast::Declaration>([&](ast::Declaration* s) {
        mlir::Location sl(loc(s));
        llvm::StringRef name = s->getName();
        mlir::Value type = gen(s->getType(), symbols);
        if (s->getIsGlobal()) {
          mlir::Value declaration = builder.create<GetGlobalOp>(sl, name, type).getOut();
          symbols.define(name, {declaration, Source::Global, sl});
        } else {
          mlir::Value declaration = builder.create<DeclarationOp>(sl, name, type).getOut();
          symbols.define(name, {declaration, Source::Declaration, sl});
        }
      })
      .Case<ast::Constraint>([&](ast::Constraint* s) {
        mlir::Value left = gen(s->getLeft(), symbols);
        mlir::Value right = gen(s->getRight(), symbols);
        builder.create<ConstraintOp>(loc(s), left, right);
      })
      .Case<ast::Void>([&](ast::Void* s) { gen(s->getValue(), symbols); })
      .Case<ast::Directive>([&](ast::Directive* s) {
        mlir::StringAttr name = builder.getStringAttr(s->getName());
        ValueVector args = gen(s->getArgs(), symbols);
        builder.create<DirectiveOp>(loc(s), name, args);
      })
      .Default([&](auto) { mlir::emitError(loc(s), "Unknown statement type"); });
}

void Impl::gen(ast::Component* c, SymbolTable& outerscope) {
  assert(c);
  curComponent = mlir::StringAttr::get(&ctx, c->getName());
  llvm::StringRef name = c->getName();
  auto op = builder.create<ComponentOp>(loc(c), name);
  if (ast::Component::Kind::Function == c->getKind()) {
    op->setAttr("function", mlir::UnitAttr::get(&ctx));
  }
  if (ast::Component::Kind::Argument == c->getKind()) {
    op->setAttr("argument", mlir::UnitAttr::get(&ctx));
  }
  if (c->getTypeParams().size()) {
    op->setAttr("generic", mlir::UnitAttr::get(&ctx));
  }

  mlir::Region* region = &op.getBody();
  builder.createBlock(region, region->begin());
  uint32_t idx = 0;
  SymbolTable typeparams(outerscope);
  for (auto& p : c->getTypeParams()) {
    mlir::Location pl(loc(p));
    llvm::StringRef pn = p->getName();
    // Evaluate the type expression in global context
    mlir::Value pt = gen(p->getType(), outerscope);
    auto val = builder.create<TypeParamOp>(pl, pn, idx++, pt);
    // Define the type parameter in the component context
    typeparams.define(pn, {val, Source::TypeParam, pl});
  }
  idx = 0;
  SymbolTable funcparams(typeparams);
  llvm::SmallVector<mlir::Value> paramvals;
  for (auto& p : c->getParams()) {
    mlir::Location pl(loc(p));
    llvm::StringRef pn = p->getName();
    mlir::Value pt = gen(p->getType(), typeparams);
    if (p->getIsVariadic() && p != c->getParams().back()) {
      mlir::emitError(loc(p)) << "only the last parameter can be variadic";
    }
    auto val = builder.create<ConstructorParamOp>(pl, pn, idx++, pt, p->getIsVariadic());
    funcparams.define(pn, {val, Source::ConstructorParam, pl});
    paramvals.push_back(val);
  }
  // Define the component name after evaluating the parameters, so their
  // type expressions cannot resolve their own component's name.
  outerscope.define(name, {mlir::Value(), Source::Component, loc(c)});
  // The component's body block is a syntactic structure, not a nested
  // block expression, so we must inline its contents into the ComponentOp.
  SymbolTable innerscope(funcparams);
  ast::Expression* body = c->getBody();
  if (!body) {
    mlir::emitError(loc(c)) << "missing body expresion";
  } else if (ast::Component::Kind::Extern == c->getKind()) {
    if (llvm::isa<ast::Block>(body)) {
      mlir::emitError(loc(c)) << "Unexpected block in extern";
    } else {
      auto returnType = gen(c->getBody(), innerscope);
      auto ext = builder.create<ExternOp>(loc(c), name, returnType, mlir::ValueRange(paramvals));
      builder.create<SuperOp>(loc(c), ext);
    }
  } else {
    if (ast::Block* b = llvm::dyn_cast<ast::Block>(body)) {
      genBlockBody(b, innerscope);
    } else {
      builder.create<SuperOp>(loc(c), gen(c->getBody(), innerscope));
    }
  }
  builder.setInsertionPointAfter(op);
  curComponent = nullptr;
}

void Impl::genBlockBody(ast::Block* b, SymbolTable& symbols) {
  assert(b);
  for (auto& s : b->getBody()) {
    gen(s.get(), symbols);
  }
  ast::Expression* tail = b->getValue();
  auto result = gen(tail, symbols);
  builder.create<SuperOp>(loc(tail), result);
}

template <typename T> mlir::Location Impl::loc(T* node) {
  assert(node);
  llvm::SMLoc loc = node->loc();
  unsigned buffer = sourceManager.FindBufferContainingLoc(loc);
  if (buffer) {
    auto file = sourceManager.getMemoryBuffer(buffer)->getBufferIdentifier();
    auto lineAndCol = sourceManager.getLineAndColumn(loc, buffer);
    unsigned line = lineAndCol.first;
    unsigned col = lineAndCol.second;
    auto fileLineColLoc = mlir::FileLineColLoc::get(&ctx, file, line, col);
    if (curComponent) {
      return mlir::NameLoc::get(curComponent, fileLineColLoc);
    } else {
      return fileLineColLoc;
    }
  } else {
    return mlir::UnknownLoc::get(&ctx);
  }
}

template <typename T> mlir::Location Impl::loc(const std::shared_ptr<T>& x) {
  // simple helper so we don't have to type foo.get() over and over
  return loc(x.get());
}

} // namespace

std::optional<mlir::ModuleOp> lower(MLIRContext& ctx, const llvm::SourceMgr& mgr, ast::Module* m) {
  // Inject a diagnostic handler to detect if any errors occurred. We can't do
  // this with an early return because we want to report as many diagnostics as
  // possible, and doing it this way is simpler than detecting the errors where
  // they are emitted.
  bool containsErrors = false;
  mlir::ScopedDiagnosticHandler scopedHandler(&ctx, [&](mlir::Diagnostic&) {
    containsErrors = true;
    return mlir::failure();
  });

  SymbolTable symbols;
  mlir::ModuleOp out = Impl(ctx, mgr).gen(m, symbols);

  if (mlir::failed(mlir::verify(out))) {
    out->emitError("zhl module verification error");
  }

  if (containsErrors) {
    return std::optional<mlir::ModuleOp>();
  }

  return out;
}

} // namespace dsl
} // namespace zirgen
