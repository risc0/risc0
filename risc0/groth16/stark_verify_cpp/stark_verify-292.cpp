#include "stark_verify.hpp"
void normalize_impl_138_run(uint ctx_index,Circom_CalcWit* ctx){
FrElement* circuitConstants = ctx->circuitConstants;
FrElement* signalValues = ctx->signalValues;
FrElement expaux[4];
FrElement lvar[3];
u64 mySignalStart = ctx->componentMemory[ctx_index].signalStart;
std::string myTemplateName = ctx->componentMemory[ctx_index].templateName;
std::string myComponentName = ctx->componentMemory[ctx_index].componentName;
u64 myFather = ctx->componentMemory[ctx_index].idFather;
u64 myId = ctx_index;
u32* mySubcomponents = ctx->componentMemory[ctx_index].subcomponents;
bool* mySubcomponentsParallel = ctx->componentMemory[ctx_index].subcomponentsParallel;
std::string* listOfTemplateMessages = ctx->listOfTemplateMessages;
uint sub_component_aux;
uint index_multiple_eq;
int cmp_index_ref_load = -1;
{
PFrElement aux_dest = &lvar[0];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[102]);
}
{
std::string new_cmp_name = "k_bits";
to_bits_exact_137_create(mySignalStart+2,0+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[0] = 0+ctx_index+1;
}
{
std::string new_cmp_name = "out_bits";
to_bits_exact_57_create(mySignalStart+75,1+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[1] = 1+ctx_index+1;
}
{
std::string new_cmp_name = "vbb";
valid_baby_bear_58_create(mySignalStart+107,2+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[2] = 2+ctx_index+1;
}
{
PFrElement aux_dest = &lvar[1];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[276]);
}
{
PFrElement aux_dest = &lvar[2];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[72]);
}
{
uint cmp_index_ref = 0;
{
PFrElement aux_dest = &ctx->signalValues[ctx->componentMemory[mySubcomponents[cmp_index_ref]].signalStart + 72];
// load src
Fr_idiv(&expaux[0],&signalValues[mySignalStart + 1],&circuitConstants[276]); // line circom 59
// end load src
Fr_copy(aux_dest,&expaux[0]);
}
// need to run sub component
ctx->componentMemory[mySubcomponents[cmp_index_ref]].inputCounter -= 1;
assert(!(ctx->componentMemory[mySubcomponents[cmp_index_ref]].inputCounter));
to_bits_exact_137_run(mySubcomponents[cmp_index_ref],ctx);
}
{
uint cmp_index_ref = 1;
{
PFrElement aux_dest = &ctx->signalValues[ctx->componentMemory[mySubcomponents[cmp_index_ref]].signalStart + 31];
// load src
Fr_mod(&expaux[0],&signalValues[mySignalStart + 1],&circuitConstants[276]); // line circom 60
// end load src
Fr_copy(aux_dest,&expaux[0]);
}
// need to run sub component
ctx->componentMemory[mySubcomponents[cmp_index_ref]].inputCounter -= 1;
assert(!(ctx->componentMemory[mySubcomponents[cmp_index_ref]].inputCounter));
to_bits_exact_57_run(mySubcomponents[cmp_index_ref],ctx);
}
{
uint cmp_index_ref = 2;
{
PFrElement aux_dest = &ctx->signalValues[ctx->componentMemory[mySubcomponents[cmp_index_ref]].signalStart + 0];
// load src
cmp_index_ref_load = 1;
cmp_index_ref_load = 1;
// end load src
Fr_copyn(aux_dest,&ctx->signalValues[ctx->componentMemory[mySubcomponents[1]].signalStart + 0],31);
}
// need to run sub component
ctx->componentMemory[mySubcomponents[cmp_index_ref]].inputCounter -= 31;
assert(!(ctx->componentMemory[mySubcomponents[cmp_index_ref]].inputCounter));
valid_baby_bear_58_run(mySubcomponents[cmp_index_ref],ctx);
}
{
cmp_index_ref_load = 0;
cmp_index_ref_load = 0;
Fr_mul(&expaux[2],&ctx->signalValues[ctx->componentMemory[mySubcomponents[0]].signalStart + 72],&circuitConstants[276]); // line circom 68
cmp_index_ref_load = 1;
cmp_index_ref_load = 1;
Fr_add(&expaux[1],&expaux[2],&ctx->signalValues[ctx->componentMemory[mySubcomponents[1]].signalStart + 31]); // line circom 68
{{
Fr_eq(&expaux[0],&expaux[1],&signalValues[mySignalStart + 1]); // line circom 68
}}
if (!Fr_isTrue(&expaux[0])) std::cout << "Failed assert in template/function " << myTemplateName << " line 68. " <<  "Followed trace of components: " << ctx->getTrace(myId) << std::endl;
assert(Fr_isTrue(&expaux[0]));
}
{
PFrElement aux_dest = &signalValues[mySignalStart + 0];
// load src
cmp_index_ref_load = 1;
cmp_index_ref_load = 1;
// end load src
Fr_copy(aux_dest,&ctx->signalValues[ctx->componentMemory[mySubcomponents[1]].signalStart + 31]);
}
for (uint i = 0; i < 3; i++){
uint index_subc = ctx->componentMemory[ctx_index].subcomponents[i];
if (index_subc != 0)release_memory_component(ctx,index_subc);
}
}
