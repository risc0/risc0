#include "stark_verify.hpp"
void poseidon_52_run(uint ctx_index,Circom_CalcWit* ctx){
FrElement* circuitConstants = ctx->circuitConstants;
FrElement* signalValues = ctx->signalValues;
FrElement expaux[2];
FrElement lvar[1];
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
std::string new_cmp_name = "init[0]";
full_round_2_create(mySignalStart+78,16+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[0] = 16+ctx_index+1;
}
{
std::string new_cmp_name = "init[1]";
full_round_3_create(mySignalStart+96,20+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[1] = 20+ctx_index+1;
}
{
std::string new_cmp_name = "init[2]";
full_round_4_create(mySignalStart+114,24+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[2] = 24+ctx_index+1;
}
{
std::string new_cmp_name = "init[3]";
full_round_5_create(mySignalStart+132,28+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[3] = 28+ctx_index+1;
}
{
std::string new_cmp_name = "mid[0]";
partial_round_6_create(mySignalStart+150,32+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[4] = 32+ctx_index+1;
}
{
std::string new_cmp_name = "mid[1]";
partial_round_7_create(mySignalStart+163,34+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[5] = 34+ctx_index+1;
}
{
std::string new_cmp_name = "mid[2]";
partial_round_8_create(mySignalStart+176,36+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[6] = 36+ctx_index+1;
}
{
std::string new_cmp_name = "mid[3]";
partial_round_9_create(mySignalStart+189,38+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[7] = 38+ctx_index+1;
}
{
std::string new_cmp_name = "mid[4]";
partial_round_10_create(mySignalStart+202,40+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[8] = 40+ctx_index+1;
}
{
std::string new_cmp_name = "mid[5]";
partial_round_11_create(mySignalStart+215,42+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[9] = 42+ctx_index+1;
}
{
std::string new_cmp_name = "mid[6]";
partial_round_12_create(mySignalStart+228,44+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[10] = 44+ctx_index+1;
}
{
std::string new_cmp_name = "mid[7]";
partial_round_13_create(mySignalStart+241,46+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[11] = 46+ctx_index+1;
}
{
std::string new_cmp_name = "mid[8]";
partial_round_14_create(mySignalStart+254,48+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[12] = 48+ctx_index+1;
}
{
std::string new_cmp_name = "mid[9]";
partial_round_15_create(mySignalStart+267,50+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[13] = 50+ctx_index+1;
}
{
std::string new_cmp_name = "mid[10]";
partial_round_16_create(mySignalStart+280,52+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[14] = 52+ctx_index+1;
}
{
std::string new_cmp_name = "mid[11]";
partial_round_17_create(mySignalStart+293,54+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[15] = 54+ctx_index+1;
}
{
std::string new_cmp_name = "mid[12]";
partial_round_18_create(mySignalStart+306,56+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[16] = 56+ctx_index+1;
}
{
std::string new_cmp_name = "mid[13]";
partial_round_19_create(mySignalStart+319,58+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[17] = 58+ctx_index+1;
}
{
std::string new_cmp_name = "mid[14]";
partial_round_20_create(mySignalStart+332,60+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[18] = 60+ctx_index+1;
}
{
std::string new_cmp_name = "mid[15]";
partial_round_21_create(mySignalStart+345,62+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[19] = 62+ctx_index+1;
}
{
std::string new_cmp_name = "mid[16]";
partial_round_22_create(mySignalStart+358,64+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[20] = 64+ctx_index+1;
}
{
std::string new_cmp_name = "mid[17]";
partial_round_23_create(mySignalStart+371,66+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[21] = 66+ctx_index+1;
}
{
std::string new_cmp_name = "mid[18]";
partial_round_24_create(mySignalStart+384,68+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[22] = 68+ctx_index+1;
}
{
std::string new_cmp_name = "mid[19]";
partial_round_25_create(mySignalStart+397,70+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[23] = 70+ctx_index+1;
}
{
std::string new_cmp_name = "mid[20]";
partial_round_26_create(mySignalStart+410,72+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[24] = 72+ctx_index+1;
}
{
std::string new_cmp_name = "mid[21]";
partial_round_27_create(mySignalStart+423,74+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[25] = 74+ctx_index+1;
}
{
std::string new_cmp_name = "mid[22]";
partial_round_28_create(mySignalStart+436,76+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[26] = 76+ctx_index+1;
}
{
std::string new_cmp_name = "mid[23]";
partial_round_29_create(mySignalStart+449,78+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[27] = 78+ctx_index+1;
}
{
std::string new_cmp_name = "mid[24]";
partial_round_30_create(mySignalStart+462,80+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[28] = 80+ctx_index+1;
}
{
std::string new_cmp_name = "mid[25]";
partial_round_31_create(mySignalStart+475,82+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[29] = 82+ctx_index+1;
}
{
std::string new_cmp_name = "mid[26]";
partial_round_32_create(mySignalStart+488,84+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[30] = 84+ctx_index+1;
}
{
std::string new_cmp_name = "mid[27]";
partial_round_33_create(mySignalStart+501,86+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[31] = 86+ctx_index+1;
}
{
std::string new_cmp_name = "mid[28]";
partial_round_34_create(mySignalStart+514,88+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[32] = 88+ctx_index+1;
}
{
std::string new_cmp_name = "mid[29]";
partial_round_35_create(mySignalStart+527,90+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[33] = 90+ctx_index+1;
}
{
std::string new_cmp_name = "mid[30]";
partial_round_36_create(mySignalStart+540,92+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[34] = 92+ctx_index+1;
}
{
std::string new_cmp_name = "mid[31]";
partial_round_37_create(mySignalStart+553,94+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[35] = 94+ctx_index+1;
}
{
std::string new_cmp_name = "mid[32]";
partial_round_38_create(mySignalStart+566,96+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[36] = 96+ctx_index+1;
}
{
std::string new_cmp_name = "mid[33]";
partial_round_39_create(mySignalStart+579,98+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[37] = 98+ctx_index+1;
}
{
std::string new_cmp_name = "mid[34]";
partial_round_40_create(mySignalStart+592,100+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[38] = 100+ctx_index+1;
}
{
std::string new_cmp_name = "mid[35]";
partial_round_41_create(mySignalStart+605,102+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[39] = 102+ctx_index+1;
}
{
std::string new_cmp_name = "mid[36]";
partial_round_42_create(mySignalStart+618,104+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[40] = 104+ctx_index+1;
}
{
std::string new_cmp_name = "mid[37]";
partial_round_43_create(mySignalStart+631,106+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[41] = 106+ctx_index+1;
}
{
std::string new_cmp_name = "mid[38]";
partial_round_44_create(mySignalStart+644,108+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[42] = 108+ctx_index+1;
}
{
std::string new_cmp_name = "mid[39]";
partial_round_45_create(mySignalStart+657,110+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[43] = 110+ctx_index+1;
}
{
std::string new_cmp_name = "mid[40]";
partial_round_46_create(mySignalStart+670,112+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[44] = 112+ctx_index+1;
}
{
std::string new_cmp_name = "mid[41]";
partial_round_47_create(mySignalStart+683,114+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[45] = 114+ctx_index+1;
}
{
std::string new_cmp_name = "fini[0]";
full_round_48_create(mySignalStart+6,0+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[46] = 0+ctx_index+1;
}
{
std::string new_cmp_name = "fini[1]";
full_round_49_create(mySignalStart+24,4+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[47] = 4+ctx_index+1;
}
{
std::string new_cmp_name = "fini[2]";
full_round_50_create(mySignalStart+42,8+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[48] = 8+ctx_index+1;
}
{
std::string new_cmp_name = "fini[3]";
full_round_51_create(mySignalStart+60,12+ctx_index+1,ctx,new_cmp_name,myId);
mySubcomponents[49] = 12+ctx_index+1;
}
{
uint cmp_index_ref = 0;
{
PFrElement aux_dest = &ctx->signalValues[ctx->componentMemory[mySubcomponents[cmp_index_ref]].signalStart + ctx->templateInsId2IOSignalInfo[ctx->componentMemory[mySubcomponents[cmp_index_ref]].templateId].defs[1].offset];
// load src
// end load src
Fr_copyn(aux_dest,&signalValues[mySignalStart + 3],3);
}
// run sub component if needed
if(!(ctx->componentMemory[mySubcomponents[cmp_index_ref]].inputCounter -= 3)){
(*_functionTable[ctx->componentMemory[mySubcomponents[cmp_index_ref]].templateId])(mySubcomponents[cmp_index_ref],ctx);

}
}
{
PFrElement aux_dest = &lvar[0];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[1]);
}
Fr_lt(&expaux[0],&lvar[0],&circuitConstants[4]); // line circom 305
while(Fr_isTrue(&expaux[0])){
{
uint cmp_index_ref = ((1 * Fr_toInt(&lvar[0])) + 0);
{
PFrElement aux_dest = &ctx->signalValues[ctx->componentMemory[mySubcomponents[cmp_index_ref]].signalStart + ctx->templateInsId2IOSignalInfo[ctx->componentMemory[mySubcomponents[cmp_index_ref]].templateId].defs[1].offset];
// load src
Fr_sub(&expaux[0],&lvar[0],&circuitConstants[1]); // line circom 307
cmp_index_ref_load = ((1 * Fr_toInt(&expaux[0])) + 0);
cmp_index_ref_load = ((1 * Fr_toInt(&expaux[0])) + 0);
// end load src
Fr_copyn(aux_dest,&ctx->signalValues[ctx->componentMemory[mySubcomponents[((1 * Fr_toInt(&expaux[0])) + 0)]].signalStart + ctx->templateInsId2IOSignalInfo[ctx->componentMemory[mySubcomponents[((1 * Fr_toInt(&expaux[0])) + 0)]].templateId].defs[0].offset],3);
}
// run sub component if needed
if(!(ctx->componentMemory[mySubcomponents[cmp_index_ref]].inputCounter -= 3)){
(*_functionTable[ctx->componentMemory[mySubcomponents[cmp_index_ref]].templateId])(mySubcomponents[cmp_index_ref],ctx);

}
}
{
PFrElement aux_dest = &lvar[0];
// load src
Fr_add(&expaux[0],&lvar[0],&circuitConstants[1]); // line circom 305
// end load src
Fr_copy(aux_dest,&expaux[0]);
}
Fr_lt(&expaux[0],&lvar[0],&circuitConstants[4]); // line circom 305
}
{
uint cmp_index_ref = 4;
{
PFrElement aux_dest = &ctx->signalValues[ctx->componentMemory[mySubcomponents[cmp_index_ref]].signalStart + ctx->templateInsId2IOSignalInfo[ctx->componentMemory[mySubcomponents[cmp_index_ref]].templateId].defs[1].offset];
// load src
cmp_index_ref_load = 3;
cmp_index_ref_load = 3;
// end load src
Fr_copyn(aux_dest,&ctx->signalValues[ctx->componentMemory[mySubcomponents[3]].signalStart + ctx->templateInsId2IOSignalInfo[ctx->componentMemory[mySubcomponents[3]].templateId].defs[0].offset],3);
}
// run sub component if needed
if(!(ctx->componentMemory[mySubcomponents[cmp_index_ref]].inputCounter -= 3)){
(*_functionTable[ctx->componentMemory[mySubcomponents[cmp_index_ref]].templateId])(mySubcomponents[cmp_index_ref],ctx);

}
}
{
PFrElement aux_dest = &lvar[0];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[1]);
}
Fr_lt(&expaux[0],&lvar[0],&circuitConstants[42]); // line circom 311
while(Fr_isTrue(&expaux[0])){
{
uint cmp_index_ref = ((1 * Fr_toInt(&lvar[0])) + 4);
{
PFrElement aux_dest = &ctx->signalValues[ctx->componentMemory[mySubcomponents[cmp_index_ref]].signalStart + ctx->templateInsId2IOSignalInfo[ctx->componentMemory[mySubcomponents[cmp_index_ref]].templateId].defs[1].offset];
// load src
Fr_sub(&expaux[0],&lvar[0],&circuitConstants[1]); // line circom 313
cmp_index_ref_load = ((1 * Fr_toInt(&expaux[0])) + 4);
cmp_index_ref_load = ((1 * Fr_toInt(&expaux[0])) + 4);
// end load src
Fr_copyn(aux_dest,&ctx->signalValues[ctx->componentMemory[mySubcomponents[((1 * Fr_toInt(&expaux[0])) + 4)]].signalStart + ctx->templateInsId2IOSignalInfo[ctx->componentMemory[mySubcomponents[((1 * Fr_toInt(&expaux[0])) + 4)]].templateId].defs[0].offset],3);
}
// run sub component if needed
if(!(ctx->componentMemory[mySubcomponents[cmp_index_ref]].inputCounter -= 3)){
(*_functionTable[ctx->componentMemory[mySubcomponents[cmp_index_ref]].templateId])(mySubcomponents[cmp_index_ref],ctx);

}
}
{
PFrElement aux_dest = &lvar[0];
// load src
Fr_add(&expaux[0],&lvar[0],&circuitConstants[1]); // line circom 311
// end load src
Fr_copy(aux_dest,&expaux[0]);
}
Fr_lt(&expaux[0],&lvar[0],&circuitConstants[42]); // line circom 311
}
{
uint cmp_index_ref = 46;
{
PFrElement aux_dest = &ctx->signalValues[ctx->componentMemory[mySubcomponents[cmp_index_ref]].signalStart + ctx->templateInsId2IOSignalInfo[ctx->componentMemory[mySubcomponents[cmp_index_ref]].templateId].defs[1].offset];
// load src
cmp_index_ref_load = 45;
cmp_index_ref_load = 45;
// end load src
Fr_copyn(aux_dest,&ctx->signalValues[ctx->componentMemory[mySubcomponents[45]].signalStart + ctx->templateInsId2IOSignalInfo[ctx->componentMemory[mySubcomponents[45]].templateId].defs[0].offset],3);
}
// run sub component if needed
if(!(ctx->componentMemory[mySubcomponents[cmp_index_ref]].inputCounter -= 3)){
(*_functionTable[ctx->componentMemory[mySubcomponents[cmp_index_ref]].templateId])(mySubcomponents[cmp_index_ref],ctx);

}
}
{
PFrElement aux_dest = &lvar[0];
// load src
// end load src
Fr_copy(aux_dest,&circuitConstants[1]);
}
Fr_lt(&expaux[0],&lvar[0],&circuitConstants[4]); // line circom 317
while(Fr_isTrue(&expaux[0])){
{
uint cmp_index_ref = ((1 * Fr_toInt(&lvar[0])) + 46);
{
PFrElement aux_dest = &ctx->signalValues[ctx->componentMemory[mySubcomponents[cmp_index_ref]].signalStart + ctx->templateInsId2IOSignalInfo[ctx->componentMemory[mySubcomponents[cmp_index_ref]].templateId].defs[1].offset];
// load src
Fr_sub(&expaux[0],&lvar[0],&circuitConstants[1]); // line circom 319
cmp_index_ref_load = ((1 * Fr_toInt(&expaux[0])) + 46);
cmp_index_ref_load = ((1 * Fr_toInt(&expaux[0])) + 46);
// end load src
Fr_copyn(aux_dest,&ctx->signalValues[ctx->componentMemory[mySubcomponents[((1 * Fr_toInt(&expaux[0])) + 46)]].signalStart + ctx->templateInsId2IOSignalInfo[ctx->componentMemory[mySubcomponents[((1 * Fr_toInt(&expaux[0])) + 46)]].templateId].defs[0].offset],3);
}
// run sub component if needed
if(!(ctx->componentMemory[mySubcomponents[cmp_index_ref]].inputCounter -= 3)){
(*_functionTable[ctx->componentMemory[mySubcomponents[cmp_index_ref]].templateId])(mySubcomponents[cmp_index_ref],ctx);

}
}
{
PFrElement aux_dest = &lvar[0];
// load src
Fr_add(&expaux[0],&lvar[0],&circuitConstants[1]); // line circom 317
// end load src
Fr_copy(aux_dest,&expaux[0]);
}
Fr_lt(&expaux[0],&lvar[0],&circuitConstants[4]); // line circom 317
}
{
PFrElement aux_dest = &signalValues[mySignalStart + 0];
// load src
cmp_index_ref_load = 49;
cmp_index_ref_load = 49;
// end load src
Fr_copyn(aux_dest,&ctx->signalValues[ctx->componentMemory[mySubcomponents[49]].signalStart + ctx->templateInsId2IOSignalInfo[ctx->componentMemory[mySubcomponents[49]].templateId].defs[0].offset],3);
}
for (uint i = 0; i < 50; i++){
uint index_subc = ctx->componentMemory[ctx_index].subcomponents[i];
if (index_subc != 0)release_memory_component(ctx,index_subc);
}
}
