#include "stark_verify.hpp"
void inverse_2(Circom_CalcWit* ctx,FrElement* lvar,uint componentFather,FrElement* destination,int destination_size){
FrElement* circuitConstants = ctx->circuitConstants;
FrElement expaux[3];
std::string myTemplateName = "inverse";
u64 myId = componentFather;
{
PFrElement aux_dest = &lvar[2];
// load src
// end load src
Fr_copy(aux_dest,&lvar[0]);
}
{
PFrElement aux_dest = &lvar[3];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[1]);
}
{
PFrElement aux_dest = &lvar[4];
// load src
Fr_sub(&expaux[0],&lvar[1],&circuitConstants[2]); // line circom 388
// end load src
Fr_copy(aux_dest,&expaux[0]);
}
Fr_neq(&expaux[0],&lvar[4],&circuitConstants[0]); // line circom 389
while(Fr_isTrue(&expaux[0])){
Fr_mod(&expaux[1],&lvar[4],&circuitConstants[2]); // line circom 390
{{
Fr_eq(&expaux[0],&expaux[1],&circuitConstants[1]); // line circom 390
}}
if(Fr_isTrue(&expaux[0])){
{
PFrElement aux_dest = &lvar[4];
// load src
Fr_sub(&expaux[0],&lvar[4],&circuitConstants[1]); // line circom 391
// end load src
Fr_copy(aux_dest,&expaux[0]);
}
{
PFrElement aux_dest = &lvar[3];
// load src
Fr_mul(&expaux[0],&lvar[3],&lvar[2]); // line circom 392
// end load src
Fr_copy(aux_dest,&expaux[0]);
}
{
PFrElement aux_dest = &lvar[3];
// load src
Fr_mod(&expaux[0],&lvar[3],&lvar[1]); // line circom 393
// end load src
Fr_copy(aux_dest,&expaux[0]);
}
}
{
PFrElement aux_dest = &lvar[2];
// load src
Fr_mul(&expaux[0],&lvar[2],&lvar[2]); // line circom 395
// end load src
Fr_copy(aux_dest,&expaux[0]);
}
{
PFrElement aux_dest = &lvar[2];
// load src
Fr_mod(&expaux[0],&lvar[2],&lvar[1]); // line circom 396
// end load src
Fr_copy(aux_dest,&expaux[0]);
}
{
PFrElement aux_dest = &lvar[4];
// load src
Fr_div(&expaux[0],&lvar[4],&circuitConstants[2]); // line circom 397
// end load src
Fr_copy(aux_dest,&expaux[0]);
}
Fr_neq(&expaux[0],&lvar[4],&circuitConstants[0]); // line circom 389
}
// return bucket
Fr_copy(destination,&lvar[3]);
return;
}
