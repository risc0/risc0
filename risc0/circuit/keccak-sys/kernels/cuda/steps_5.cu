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

#include "steps.cuh"
#include "witgen.h"

namespace risc0::circuit::keccak::cuda {

__device__ NondetRegStruct exec_IsZero(ExecContext& ctx,
                                       Val arg0,
                                       BoundLayout<IsZeroLayout> layout1) {
  // IsZero(zirgen/circuit/keccak2/is_zero.zir:8)
  NondetRegStruct x2 = exec_NondetReg(ctx, isz(arg0), LAYOUT_LOOKUP(layout1, _super));
  // IsZero(zirgen/circuit/keccak2/is_zero.zir:11)
  NondetRegStruct x3 = exec_NondetReg(ctx, inv_0(arg0), LAYOUT_LOOKUP(layout1, inv));
  // AssertBit(zirgen/circuit/keccak2/bits.zir:6)
  // IsZero(zirgen/circuit/keccak2/is_zero.zir:14)
  Val x4 = (Val(1) - x2._super);
  EQZ((x2._super * x4),
      "loc(callsite( AssertBit ( zirgen/circuit/keccak2/bits.zir :6:20) at  IsZero ( "
      "zirgen/circuit/keccak2/is_zero.zir :14:13)))");
  // IsZero(zirgen/circuit/keccak2/is_zero.zir:16)
  EQZ(((arg0 * x3._super) - x4), "IsZero(zirgen/circuit/keccak2/is_zero.zir:16)");
  // IsZero(zirgen/circuit/keccak2/is_zero.zir:18)
  EQZ((x2._super * arg0), "IsZero(zirgen/circuit/keccak2/is_zero.zir:18)");
  // IsZero(zirgen/circuit/keccak2/is_zero.zir:20)
  EQZ((x2._super * x3._super), "IsZero(zirgen/circuit/keccak2/is_zero.zir:20)");
  return x2;
}
__device__ TopStateStruct exec_ShaCycle(ExecContext& ctx,
                                        TopStateStruct arg0,
                                        TopStateStruct arg1,
                                        Val arg2,
                                        Val arg3,
                                        BoundLayout<ShaCycleLayout> layout4) {
  // Log(<preamble>:22)
  // ShaCycle(zirgen/circuit/keccak2/top.zir:187)
  INVOKE_EXTERN(ctx, log, "ShaCycle", std::initializer_list<Val>{arg3, arg2});
  // LoadShaState(zirgen/circuit/keccak2/top.zir:148)
  // ShaCycle(zirgen/circuit/keccak2/top.zir:189)
  Val32Array x5 = Val32Array{
      arg0.bits[224]._super._super, arg0.bits[225]._super._super, arg0.bits[226]._super._super,
      arg0.bits[227]._super._super, arg0.bits[228]._super._super, arg0.bits[229]._super._super,
      arg0.bits[230]._super._super, arg0.bits[231]._super._super, arg0.bits[232]._super._super,
      arg0.bits[233]._super._super, arg0.bits[234]._super._super, arg0.bits[235]._super._super,
      arg0.bits[236]._super._super, arg0.bits[237]._super._super, arg0.bits[238]._super._super,
      arg0.bits[239]._super._super, arg0.bits[240]._super._super, arg0.bits[241]._super._super,
      arg0.bits[242]._super._super, arg0.bits[243]._super._super, arg0.bits[244]._super._super,
      arg0.bits[245]._super._super, arg0.bits[246]._super._super, arg0.bits[247]._super._super,
      arg0.bits[248]._super._super, arg0.bits[249]._super._super, arg0.bits[250]._super._super,
      arg0.bits[251]._super._super, arg0.bits[252]._super._super, arg0.bits[253]._super._super,
      arg0.bits[254]._super._super, arg0.bits[255]._super._super};
  Val32Array x6 = Val32Array{
      arg0.bits[192]._super._super, arg0.bits[193]._super._super, arg0.bits[194]._super._super,
      arg0.bits[195]._super._super, arg0.bits[196]._super._super, arg0.bits[197]._super._super,
      arg0.bits[198]._super._super, arg0.bits[199]._super._super, arg0.bits[200]._super._super,
      arg0.bits[201]._super._super, arg0.bits[202]._super._super, arg0.bits[203]._super._super,
      arg0.bits[204]._super._super, arg0.bits[205]._super._super, arg0.bits[206]._super._super,
      arg0.bits[207]._super._super, arg0.bits[208]._super._super, arg0.bits[209]._super._super,
      arg0.bits[210]._super._super, arg0.bits[211]._super._super, arg0.bits[212]._super._super,
      arg0.bits[213]._super._super, arg0.bits[214]._super._super, arg0.bits[215]._super._super,
      arg0.bits[216]._super._super, arg0.bits[217]._super._super, arg0.bits[218]._super._super,
      arg0.bits[219]._super._super, arg0.bits[220]._super._super, arg0.bits[221]._super._super,
      arg0.bits[222]._super._super, arg0.bits[223]._super._super};
  Val32Array x7 = Val32Array{
      arg0.bits[160]._super._super, arg0.bits[161]._super._super, arg0.bits[162]._super._super,
      arg0.bits[163]._super._super, arg0.bits[164]._super._super, arg0.bits[165]._super._super,
      arg0.bits[166]._super._super, arg0.bits[167]._super._super, arg0.bits[168]._super._super,
      arg0.bits[169]._super._super, arg0.bits[170]._super._super, arg0.bits[171]._super._super,
      arg0.bits[172]._super._super, arg0.bits[173]._super._super, arg0.bits[174]._super._super,
      arg0.bits[175]._super._super, arg0.bits[176]._super._super, arg0.bits[177]._super._super,
      arg0.bits[178]._super._super, arg0.bits[179]._super._super, arg0.bits[180]._super._super,
      arg0.bits[181]._super._super, arg0.bits[182]._super._super, arg0.bits[183]._super._super,
      arg0.bits[184]._super._super, arg0.bits[185]._super._super, arg0.bits[186]._super._super,
      arg0.bits[187]._super._super, arg0.bits[188]._super._super, arg0.bits[189]._super._super,
      arg0.bits[190]._super._super, arg0.bits[191]._super._super};
  Val32Array x8 = Val32Array{
      arg0.bits[128]._super._super, arg0.bits[129]._super._super, arg0.bits[130]._super._super,
      arg0.bits[131]._super._super, arg0.bits[132]._super._super, arg0.bits[133]._super._super,
      arg0.bits[134]._super._super, arg0.bits[135]._super._super, arg0.bits[136]._super._super,
      arg0.bits[137]._super._super, arg0.bits[138]._super._super, arg0.bits[139]._super._super,
      arg0.bits[140]._super._super, arg0.bits[141]._super._super, arg0.bits[142]._super._super,
      arg0.bits[143]._super._super, arg0.bits[144]._super._super, arg0.bits[145]._super._super,
      arg0.bits[146]._super._super, arg0.bits[147]._super._super, arg0.bits[148]._super._super,
      arg0.bits[149]._super._super, arg0.bits[150]._super._super, arg0.bits[151]._super._super,
      arg0.bits[152]._super._super, arg0.bits[153]._super._super, arg0.bits[154]._super._super,
      arg0.bits[155]._super._super, arg0.bits[156]._super._super, arg0.bits[157]._super._super,
      arg0.bits[158]._super._super, arg0.bits[159]._super._super};
  // LoadShaState(zirgen/circuit/keccak2/top.zir:149)
  Val32Array x9 = Val32Array{
      arg0.bits[480]._super._super, arg0.bits[481]._super._super, arg0.bits[482]._super._super,
      arg0.bits[483]._super._super, arg0.bits[484]._super._super, arg0.bits[485]._super._super,
      arg0.bits[486]._super._super, arg0.bits[487]._super._super, arg0.bits[488]._super._super,
      arg0.bits[489]._super._super, arg0.bits[490]._super._super, arg0.bits[491]._super._super,
      arg0.bits[492]._super._super, arg0.bits[493]._super._super, arg0.bits[494]._super._super,
      arg0.bits[495]._super._super, arg0.bits[496]._super._super, arg0.bits[497]._super._super,
      arg0.bits[498]._super._super, arg0.bits[499]._super._super, arg0.bits[500]._super._super,
      arg0.bits[501]._super._super, arg0.bits[502]._super._super, arg0.bits[503]._super._super,
      arg0.bits[504]._super._super, arg0.bits[505]._super._super, arg0.bits[506]._super._super,
      arg0.bits[507]._super._super, arg0.bits[508]._super._super, arg0.bits[509]._super._super,
      arg0.bits[510]._super._super, arg0.bits[511]._super._super};
  Val32Array x10 = Val32Array{
      arg0.bits[448]._super._super, arg0.bits[449]._super._super, arg0.bits[450]._super._super,
      arg0.bits[451]._super._super, arg0.bits[452]._super._super, arg0.bits[453]._super._super,
      arg0.bits[454]._super._super, arg0.bits[455]._super._super, arg0.bits[456]._super._super,
      arg0.bits[457]._super._super, arg0.bits[458]._super._super, arg0.bits[459]._super._super,
      arg0.bits[460]._super._super, arg0.bits[461]._super._super, arg0.bits[462]._super._super,
      arg0.bits[463]._super._super, arg0.bits[464]._super._super, arg0.bits[465]._super._super,
      arg0.bits[466]._super._super, arg0.bits[467]._super._super, arg0.bits[468]._super._super,
      arg0.bits[469]._super._super, arg0.bits[470]._super._super, arg0.bits[471]._super._super,
      arg0.bits[472]._super._super, arg0.bits[473]._super._super, arg0.bits[474]._super._super,
      arg0.bits[475]._super._super, arg0.bits[476]._super._super, arg0.bits[477]._super._super,
      arg0.bits[478]._super._super, arg0.bits[479]._super._super};
  Val32Array x11 = Val32Array{
      arg0.bits[416]._super._super, arg0.bits[417]._super._super, arg0.bits[418]._super._super,
      arg0.bits[419]._super._super, arg0.bits[420]._super._super, arg0.bits[421]._super._super,
      arg0.bits[422]._super._super, arg0.bits[423]._super._super, arg0.bits[424]._super._super,
      arg0.bits[425]._super._super, arg0.bits[426]._super._super, arg0.bits[427]._super._super,
      arg0.bits[428]._super._super, arg0.bits[429]._super._super, arg0.bits[430]._super._super,
      arg0.bits[431]._super._super, arg0.bits[432]._super._super, arg0.bits[433]._super._super,
      arg0.bits[434]._super._super, arg0.bits[435]._super._super, arg0.bits[436]._super._super,
      arg0.bits[437]._super._super, arg0.bits[438]._super._super, arg0.bits[439]._super._super,
      arg0.bits[440]._super._super, arg0.bits[441]._super._super, arg0.bits[442]._super._super,
      arg0.bits[443]._super._super, arg0.bits[444]._super._super, arg0.bits[445]._super._super,
      arg0.bits[446]._super._super, arg0.bits[447]._super._super};
  Val32Array x12 = Val32Array{
      arg0.bits[384]._super._super, arg0.bits[385]._super._super, arg0.bits[386]._super._super,
      arg0.bits[387]._super._super, arg0.bits[388]._super._super, arg0.bits[389]._super._super,
      arg0.bits[390]._super._super, arg0.bits[391]._super._super, arg0.bits[392]._super._super,
      arg0.bits[393]._super._super, arg0.bits[394]._super._super, arg0.bits[395]._super._super,
      arg0.bits[396]._super._super, arg0.bits[397]._super._super, arg0.bits[398]._super._super,
      arg0.bits[399]._super._super, arg0.bits[400]._super._super, arg0.bits[401]._super._super,
      arg0.bits[402]._super._super, arg0.bits[403]._super._super, arg0.bits[404]._super._super,
      arg0.bits[405]._super._super, arg0.bits[406]._super._super, arg0.bits[407]._super._super,
      arg0.bits[408]._super._super, arg0.bits[409]._super._super, arg0.bits[410]._super._super,
      arg0.bits[411]._super._super, arg0.bits[412]._super._super, arg0.bits[413]._super._super,
      arg0.bits[414]._super._super, arg0.bits[415]._super._super};
  // LoadShaState(zirgen/circuit/keccak2/top.zir:150)
  Val32Array x13 = Val32Array{
      arg0.bits[736]._super._super, arg0.bits[737]._super._super, arg0.bits[738]._super._super,
      arg0.bits[739]._super._super, arg0.bits[740]._super._super, arg0.bits[741]._super._super,
      arg0.bits[742]._super._super, arg0.bits[743]._super._super, arg0.bits[744]._super._super,
      arg0.bits[745]._super._super, arg0.bits[746]._super._super, arg0.bits[747]._super._super,
      arg0.bits[748]._super._super, arg0.bits[749]._super._super, arg0.bits[750]._super._super,
      arg0.bits[751]._super._super, arg0.bits[752]._super._super, arg0.bits[753]._super._super,
      arg0.bits[754]._super._super, arg0.bits[755]._super._super, arg0.bits[756]._super._super,
      arg0.bits[757]._super._super, arg0.bits[758]._super._super, arg0.bits[759]._super._super,
      arg0.bits[760]._super._super, arg0.bits[761]._super._super, arg0.bits[762]._super._super,
      arg0.bits[763]._super._super, arg0.bits[764]._super._super, arg0.bits[765]._super._super,
      arg0.bits[766]._super._super, arg0.bits[767]._super._super};
  Val32Array x14 = Val32Array{
      arg0.bits[704]._super._super, arg0.bits[705]._super._super, arg0.bits[706]._super._super,
      arg0.bits[707]._super._super, arg0.bits[708]._super._super, arg0.bits[709]._super._super,
      arg0.bits[710]._super._super, arg0.bits[711]._super._super, arg0.bits[712]._super._super,
      arg0.bits[713]._super._super, arg0.bits[714]._super._super, arg0.bits[715]._super._super,
      arg0.bits[716]._super._super, arg0.bits[717]._super._super, arg0.bits[718]._super._super,
      arg0.bits[719]._super._super, arg0.bits[720]._super._super, arg0.bits[721]._super._super,
      arg0.bits[722]._super._super, arg0.bits[723]._super._super, arg0.bits[724]._super._super,
      arg0.bits[725]._super._super, arg0.bits[726]._super._super, arg0.bits[727]._super._super,
      arg0.bits[728]._super._super, arg0.bits[729]._super._super, arg0.bits[730]._super._super,
      arg0.bits[731]._super._super, arg0.bits[732]._super._super, arg0.bits[733]._super._super,
      arg0.bits[734]._super._super, arg0.bits[735]._super._super};
  Val32Array x15 = Val32Array{
      arg0.bits[672]._super._super, arg0.bits[673]._super._super, arg0.bits[674]._super._super,
      arg0.bits[675]._super._super, arg0.bits[676]._super._super, arg0.bits[677]._super._super,
      arg0.bits[678]._super._super, arg0.bits[679]._super._super, arg0.bits[680]._super._super,
      arg0.bits[681]._super._super, arg0.bits[682]._super._super, arg0.bits[683]._super._super,
      arg0.bits[684]._super._super, arg0.bits[685]._super._super, arg0.bits[686]._super._super,
      arg0.bits[687]._super._super, arg0.bits[688]._super._super, arg0.bits[689]._super._super,
      arg0.bits[690]._super._super, arg0.bits[691]._super._super, arg0.bits[692]._super._super,
      arg0.bits[693]._super._super, arg0.bits[694]._super._super, arg0.bits[695]._super._super,
      arg0.bits[696]._super._super, arg0.bits[697]._super._super, arg0.bits[698]._super._super,
      arg0.bits[699]._super._super, arg0.bits[700]._super._super, arg0.bits[701]._super._super,
      arg0.bits[702]._super._super, arg0.bits[703]._super._super};
  Val32Array x16 = Val32Array{
      arg0.bits[640]._super._super, arg0.bits[641]._super._super, arg0.bits[642]._super._super,
      arg0.bits[643]._super._super, arg0.bits[644]._super._super, arg0.bits[645]._super._super,
      arg0.bits[646]._super._super, arg0.bits[647]._super._super, arg0.bits[648]._super._super,
      arg0.bits[649]._super._super, arg0.bits[650]._super._super, arg0.bits[651]._super._super,
      arg0.bits[652]._super._super, arg0.bits[653]._super._super, arg0.bits[654]._super._super,
      arg0.bits[655]._super._super, arg0.bits[656]._super._super, arg0.bits[657]._super._super,
      arg0.bits[658]._super._super, arg0.bits[659]._super._super, arg0.bits[660]._super._super,
      arg0.bits[661]._super._super, arg0.bits[662]._super._super, arg0.bits[663]._super._super,
      arg0.bits[664]._super._super, arg0.bits[665]._super._super, arg0.bits[666]._super._super,
      arg0.bits[667]._super._super, arg0.bits[668]._super._super, arg0.bits[669]._super._super,
      arg0.bits[670]._super._super, arg0.bits[671]._super._super};
  Val32Array x17 = Val32Array{
      arg0.bits[608]._super._super, arg0.bits[609]._super._super, arg0.bits[610]._super._super,
      arg0.bits[611]._super._super, arg0.bits[612]._super._super, arg0.bits[613]._super._super,
      arg0.bits[614]._super._super, arg0.bits[615]._super._super, arg0.bits[616]._super._super,
      arg0.bits[617]._super._super, arg0.bits[618]._super._super, arg0.bits[619]._super._super,
      arg0.bits[620]._super._super, arg0.bits[621]._super._super, arg0.bits[622]._super._super,
      arg0.bits[623]._super._super, arg0.bits[624]._super._super, arg0.bits[625]._super._super,
      arg0.bits[626]._super._super, arg0.bits[627]._super._super, arg0.bits[628]._super._super,
      arg0.bits[629]._super._super, arg0.bits[630]._super._super, arg0.bits[631]._super._super,
      arg0.bits[632]._super._super, arg0.bits[633]._super._super, arg0.bits[634]._super._super,
      arg0.bits[635]._super._super, arg0.bits[636]._super._super, arg0.bits[637]._super._super,
      arg0.bits[638]._super._super, arg0.bits[639]._super._super};
  Val32Array x18 = Val32Array{
      arg0.bits[576]._super._super, arg0.bits[577]._super._super, arg0.bits[578]._super._super,
      arg0.bits[579]._super._super, arg0.bits[580]._super._super, arg0.bits[581]._super._super,
      arg0.bits[582]._super._super, arg0.bits[583]._super._super, arg0.bits[584]._super._super,
      arg0.bits[585]._super._super, arg0.bits[586]._super._super, arg0.bits[587]._super._super,
      arg0.bits[588]._super._super, arg0.bits[589]._super._super, arg0.bits[590]._super._super,
      arg0.bits[591]._super._super, arg0.bits[592]._super._super, arg0.bits[593]._super._super,
      arg0.bits[594]._super._super, arg0.bits[595]._super._super, arg0.bits[596]._super._super,
      arg0.bits[597]._super._super, arg0.bits[598]._super._super, arg0.bits[599]._super._super,
      arg0.bits[600]._super._super, arg0.bits[601]._super._super, arg0.bits[602]._super._super,
      arg0.bits[603]._super._super, arg0.bits[604]._super._super, arg0.bits[605]._super._super,
      arg0.bits[606]._super._super, arg0.bits[607]._super._super};
  Val32Array x19 = Val32Array{
      arg0.bits[544]._super._super, arg0.bits[545]._super._super, arg0.bits[546]._super._super,
      arg0.bits[547]._super._super, arg0.bits[548]._super._super, arg0.bits[549]._super._super,
      arg0.bits[550]._super._super, arg0.bits[551]._super._super, arg0.bits[552]._super._super,
      arg0.bits[553]._super._super, arg0.bits[554]._super._super, arg0.bits[555]._super._super,
      arg0.bits[556]._super._super, arg0.bits[557]._super._super, arg0.bits[558]._super._super,
      arg0.bits[559]._super._super, arg0.bits[560]._super._super, arg0.bits[561]._super._super,
      arg0.bits[562]._super._super, arg0.bits[563]._super._super, arg0.bits[564]._super._super,
      arg0.bits[565]._super._super, arg0.bits[566]._super._super, arg0.bits[567]._super._super,
      arg0.bits[568]._super._super, arg0.bits[569]._super._super, arg0.bits[570]._super._super,
      arg0.bits[571]._super._super, arg0.bits[572]._super._super, arg0.bits[573]._super._super,
      arg0.bits[574]._super._super, arg0.bits[575]._super._super};
  Val32Array x20 = Val32Array{
      arg0.bits[512]._super._super, arg0.bits[513]._super._super, arg0.bits[514]._super._super,
      arg0.bits[515]._super._super, arg0.bits[516]._super._super, arg0.bits[517]._super._super,
      arg0.bits[518]._super._super, arg0.bits[519]._super._super, arg0.bits[520]._super._super,
      arg0.bits[521]._super._super, arg0.bits[522]._super._super, arg0.bits[523]._super._super,
      arg0.bits[524]._super._super, arg0.bits[525]._super._super, arg0.bits[526]._super._super,
      arg0.bits[527]._super._super, arg0.bits[528]._super._super, arg0.bits[529]._super._super,
      arg0.bits[530]._super._super, arg0.bits[531]._super._super, arg0.bits[532]._super._super,
      arg0.bits[533]._super._super, arg0.bits[534]._super._super, arg0.bits[535]._super._super,
      arg0.bits[536]._super._super, arg0.bits[537]._super._super, arg0.bits[538]._super._super,
      arg0.bits[539]._super._super, arg0.bits[540]._super._super, arg0.bits[541]._super._super,
      arg0.bits[542]._super._super, arg0.bits[543]._super._super};
  Val32Array x21 = Val32Array{
      arg1.bits[736]._super._super, arg1.bits[737]._super._super, arg1.bits[738]._super._super,
      arg1.bits[739]._super._super, arg1.bits[740]._super._super, arg1.bits[741]._super._super,
      arg1.bits[742]._super._super, arg1.bits[743]._super._super, arg1.bits[744]._super._super,
      arg1.bits[745]._super._super, arg1.bits[746]._super._super, arg1.bits[747]._super._super,
      arg1.bits[748]._super._super, arg1.bits[749]._super._super, arg1.bits[750]._super._super,
      arg1.bits[751]._super._super, arg1.bits[752]._super._super, arg1.bits[753]._super._super,
      arg1.bits[754]._super._super, arg1.bits[755]._super._super, arg1.bits[756]._super._super,
      arg1.bits[757]._super._super, arg1.bits[758]._super._super, arg1.bits[759]._super._super,
      arg1.bits[760]._super._super, arg1.bits[761]._super._super, arg1.bits[762]._super._super,
      arg1.bits[763]._super._super, arg1.bits[764]._super._super, arg1.bits[765]._super._super,
      arg1.bits[766]._super._super, arg1.bits[767]._super._super};
  Val32Array x22 = Val32Array{
      arg1.bits[704]._super._super, arg1.bits[705]._super._super, arg1.bits[706]._super._super,
      arg1.bits[707]._super._super, arg1.bits[708]._super._super, arg1.bits[709]._super._super,
      arg1.bits[710]._super._super, arg1.bits[711]._super._super, arg1.bits[712]._super._super,
      arg1.bits[713]._super._super, arg1.bits[714]._super._super, arg1.bits[715]._super._super,
      arg1.bits[716]._super._super, arg1.bits[717]._super._super, arg1.bits[718]._super._super,
      arg1.bits[719]._super._super, arg1.bits[720]._super._super, arg1.bits[721]._super._super,
      arg1.bits[722]._super._super, arg1.bits[723]._super._super, arg1.bits[724]._super._super,
      arg1.bits[725]._super._super, arg1.bits[726]._super._super, arg1.bits[727]._super._super,
      arg1.bits[728]._super._super, arg1.bits[729]._super._super, arg1.bits[730]._super._super,
      arg1.bits[731]._super._super, arg1.bits[732]._super._super, arg1.bits[733]._super._super,
      arg1.bits[734]._super._super, arg1.bits[735]._super._super};
  Val32Array x23 = Val32Array{
      arg1.bits[672]._super._super, arg1.bits[673]._super._super, arg1.bits[674]._super._super,
      arg1.bits[675]._super._super, arg1.bits[676]._super._super, arg1.bits[677]._super._super,
      arg1.bits[678]._super._super, arg1.bits[679]._super._super, arg1.bits[680]._super._super,
      arg1.bits[681]._super._super, arg1.bits[682]._super._super, arg1.bits[683]._super._super,
      arg1.bits[684]._super._super, arg1.bits[685]._super._super, arg1.bits[686]._super._super,
      arg1.bits[687]._super._super, arg1.bits[688]._super._super, arg1.bits[689]._super._super,
      arg1.bits[690]._super._super, arg1.bits[691]._super._super, arg1.bits[692]._super._super,
      arg1.bits[693]._super._super, arg1.bits[694]._super._super, arg1.bits[695]._super._super,
      arg1.bits[696]._super._super, arg1.bits[697]._super._super, arg1.bits[698]._super._super,
      arg1.bits[699]._super._super, arg1.bits[700]._super._super, arg1.bits[701]._super._super,
      arg1.bits[702]._super._super, arg1.bits[703]._super._super};
  Val32Array x24 = Val32Array{
      arg1.bits[640]._super._super, arg1.bits[641]._super._super, arg1.bits[642]._super._super,
      arg1.bits[643]._super._super, arg1.bits[644]._super._super, arg1.bits[645]._super._super,
      arg1.bits[646]._super._super, arg1.bits[647]._super._super, arg1.bits[648]._super._super,
      arg1.bits[649]._super._super, arg1.bits[650]._super._super, arg1.bits[651]._super._super,
      arg1.bits[652]._super._super, arg1.bits[653]._super._super, arg1.bits[654]._super._super,
      arg1.bits[655]._super._super, arg1.bits[656]._super._super, arg1.bits[657]._super._super,
      arg1.bits[658]._super._super, arg1.bits[659]._super._super, arg1.bits[660]._super._super,
      arg1.bits[661]._super._super, arg1.bits[662]._super._super, arg1.bits[663]._super._super,
      arg1.bits[664]._super._super, arg1.bits[665]._super._super, arg1.bits[666]._super._super,
      arg1.bits[667]._super._super, arg1.bits[668]._super._super, arg1.bits[669]._super._super,
      arg1.bits[670]._super._super, arg1.bits[671]._super._super};
  Val32Array x25 = Val32Array{
      arg1.bits[608]._super._super, arg1.bits[609]._super._super, arg1.bits[610]._super._super,
      arg1.bits[611]._super._super, arg1.bits[612]._super._super, arg1.bits[613]._super._super,
      arg1.bits[614]._super._super, arg1.bits[615]._super._super, arg1.bits[616]._super._super,
      arg1.bits[617]._super._super, arg1.bits[618]._super._super, arg1.bits[619]._super._super,
      arg1.bits[620]._super._super, arg1.bits[621]._super._super, arg1.bits[622]._super._super,
      arg1.bits[623]._super._super, arg1.bits[624]._super._super, arg1.bits[625]._super._super,
      arg1.bits[626]._super._super, arg1.bits[627]._super._super, arg1.bits[628]._super._super,
      arg1.bits[629]._super._super, arg1.bits[630]._super._super, arg1.bits[631]._super._super,
      arg1.bits[632]._super._super, arg1.bits[633]._super._super, arg1.bits[634]._super._super,
      arg1.bits[635]._super._super, arg1.bits[636]._super._super, arg1.bits[637]._super._super,
      arg1.bits[638]._super._super, arg1.bits[639]._super._super};
  Val32Array x26 = Val32Array{
      arg1.bits[576]._super._super, arg1.bits[577]._super._super, arg1.bits[578]._super._super,
      arg1.bits[579]._super._super, arg1.bits[580]._super._super, arg1.bits[581]._super._super,
      arg1.bits[582]._super._super, arg1.bits[583]._super._super, arg1.bits[584]._super._super,
      arg1.bits[585]._super._super, arg1.bits[586]._super._super, arg1.bits[587]._super._super,
      arg1.bits[588]._super._super, arg1.bits[589]._super._super, arg1.bits[590]._super._super,
      arg1.bits[591]._super._super, arg1.bits[592]._super._super, arg1.bits[593]._super._super,
      arg1.bits[594]._super._super, arg1.bits[595]._super._super, arg1.bits[596]._super._super,
      arg1.bits[597]._super._super, arg1.bits[598]._super._super, arg1.bits[599]._super._super,
      arg1.bits[600]._super._super, arg1.bits[601]._super._super, arg1.bits[602]._super._super,
      arg1.bits[603]._super._super, arg1.bits[604]._super._super, arg1.bits[605]._super._super,
      arg1.bits[606]._super._super, arg1.bits[607]._super._super};
  Val32Array x27 = Val32Array{
      arg1.bits[544]._super._super, arg1.bits[545]._super._super, arg1.bits[546]._super._super,
      arg1.bits[547]._super._super, arg1.bits[548]._super._super, arg1.bits[549]._super._super,
      arg1.bits[550]._super._super, arg1.bits[551]._super._super, arg1.bits[552]._super._super,
      arg1.bits[553]._super._super, arg1.bits[554]._super._super, arg1.bits[555]._super._super,
      arg1.bits[556]._super._super, arg1.bits[557]._super._super, arg1.bits[558]._super._super,
      arg1.bits[559]._super._super, arg1.bits[560]._super._super, arg1.bits[561]._super._super,
      arg1.bits[562]._super._super, arg1.bits[563]._super._super, arg1.bits[564]._super._super,
      arg1.bits[565]._super._super, arg1.bits[566]._super._super, arg1.bits[567]._super._super,
      arg1.bits[568]._super._super, arg1.bits[569]._super._super, arg1.bits[570]._super._super,
      arg1.bits[571]._super._super, arg1.bits[572]._super._super, arg1.bits[573]._super._super,
      arg1.bits[574]._super._super, arg1.bits[575]._super._super};
  Val32Array x28 = Val32Array{
      arg1.bits[512]._super._super, arg1.bits[513]._super._super, arg1.bits[514]._super._super,
      arg1.bits[515]._super._super, arg1.bits[516]._super._super, arg1.bits[517]._super._super,
      arg1.bits[518]._super._super, arg1.bits[519]._super._super, arg1.bits[520]._super._super,
      arg1.bits[521]._super._super, arg1.bits[522]._super._super, arg1.bits[523]._super._super,
      arg1.bits[524]._super._super, arg1.bits[525]._super._super, arg1.bits[526]._super._super,
      arg1.bits[527]._super._super, arg1.bits[528]._super._super, arg1.bits[529]._super._super,
      arg1.bits[530]._super._super, arg1.bits[531]._super._super, arg1.bits[532]._super._super,
      arg1.bits[533]._super._super, arg1.bits[534]._super._super, arg1.bits[535]._super._super,
      arg1.bits[536]._super._super, arg1.bits[537]._super._super, arg1.bits[538]._super._super,
      arg1.bits[539]._super._super, arg1.bits[540]._super._super, arg1.bits[541]._super._super,
      arg1.bits[542]._super._super, arg1.bits[543]._super._super};
  // ShaCycle(zirgen/circuit/keccak2/top.zir:190)
  OneHot_8_Struct x29 = exec_OneHot_8_(ctx, arg2, LAYOUT_LOOKUP(layout4, oneHot));
  Val x30;
  if (to_size_t(x29._super[0]._super)) {
    x30 = Val(1);
  } else if (to_size_t(x29._super[1]._super)) {
    x30 = Val(1);
  } else if (to_size_t(x29._super[2]._super)) {
    x30 = Val(0);
  } else if (to_size_t(x29._super[3]._super)) {
    x30 = Val(0);
  } else if (to_size_t(x29._super[4]._super)) {
    x30 = Val(0);
  } else if (to_size_t(x29._super[5]._super)) {
    x30 = Val(0);
  } else if (to_size_t(x29._super[6]._super)) {
    x30 = Val(0);
  } else if (to_size_t(x29._super[7]._super)) {
    x30 = Val(0);
  } else {
    assert(0 && "Reached unreachable mux arm");
  }
  // ShaCycle(zirgen/circuit/keccak2/top.zir:191)
  NondetRegStruct x31 = exec_Reg(ctx, x30, LAYOUT_LOOKUP(layout4, isLoad));
  // GetK8(zirgen/circuit/keccak2/top.zir:125)
  // ShaCycle(zirgen/circuit/keccak2/top.zir:192)
  Val x32 = (x29._super[0]._super * Val(12184));
  Val x33 = (x29._super[1]._super * Val(43672));
  Val x34 = (x29._super[2]._super * Val(27073));
  Val x35 = (x29._super[3]._super * Val(20818));
  Val x36 = (x29._super[4]._super * Val(2693));
  Val x37 = (x29._super[5]._super * Val(59553));
  Val x38 = (x29._super[6]._super * Val(49430));
  Val x39 = (x29._super[7]._super * Val(33518));
  Val x40 = (((x32 + x33) + x34) + x35);
  Val x41 = (((x40 + x36) + x37) + x38);
  Val x42 = (x29._super[0]._super * Val(17034));
  Val x43 = (x29._super[1]._super * Val(55303));
  Val x44 = (x29._super[2]._super * Val(58523));
  Val x45 = (x29._super[3]._super * Val(38974));
  Val x46 = (x29._super[4]._super * Val(10167));
  Val x47 = (x29._super[5]._super * Val(41663));
  Val x48 = (x29._super[6]._super * Val(6564));
  Val x49 = (x29._super[7]._super * Val(29839));
  Val x50 = (((x42 + x43) + x44) + x45);
  Val x51 = (((x50 + x46) + x47) + x48);
  Val x52 = (x29._super[0]._super * Val(17553));
  Val x53 = (x29._super[1]._super * Val(23297));
  Val x54 = (x29._super[2]._super * Val(18310));
  Val x55 = (x29._super[3]._super * Val(50797));
  Val x56 = (x29._super[4]._super * Val(8504));
  Val x57 = (x29._super[5]._super * Val(26187));
  Val x58 = (x29._super[6]._super * Val(27656));
  Val x59 = (x29._super[7]._super * Val(25455));
  Val x60 = (((x52 + x53) + x54) + x55);
  Val x61 = (((x60 + x56) + x57) + x58);
  Val x62 = (x29._super[0]._super * Val(28983));
  Val x63 = (x29._super[1]._super * Val(4739));
  Val x64 = (x29._super[2]._super * Val(61374));
  Val x65 = (x29._super[3]._super * Val(43057));
  Val x66 = (x29._super[4]._super * Val(11803));
  Val x67 = (x29._super[5]._super * Val(43034));
  Val x68 = (x29._super[6]._super * Val(7735));
  Val x69 = (x29._super[7]._super * Val(30885));
  Val x70 = (((x62 + x63) + x64) + x65);
  Val x71 = (((x70 + x66) + x67) + x68);
  Val x72 = (x29._super[0]._super * Val(64463));
  Val x73 = (x29._super[1]._super * Val(34238));
  Val x74 = (x29._super[2]._super * Val(40390));
  Val x75 = (x29._super[3]._super * Val(10184));
  Val x76 = (x29._super[4]._super * Val(28156));
  Val x77 = (x29._super[5]._super * Val(35696));
  Val x78 = (x29._super[6]._super * Val(30540));
  Val x79 = (x29._super[7]._super * Val(30740));
  Val x80 = (((x72 + x73) + x74) + x75);
  Val x81 = (((x80 + x76) + x77) + x78);
  Val x82 = (x29._super[0]._super * Val(46528));
  Val x83 = (x29._super[1]._super * Val(9265));
  Val x84 = (x29._super[2]._super * Val(4033));
  Val x85 = (x29._super[3]._super * Val(45059));
  Val x86 = (x29._super[4]._super * Val(19756));
  Val x87 = (x29._super[5]._super * Val(49739));
  Val x88 = (x29._super[6]._super * Val(10056));
  Val x89 = (x29._super[7]._super * Val(33992));
  Val x90 = (((x82 + x83) + x84) + x85);
  Val x91 = (((x90 + x86) + x87) + x88);
  Val x92 = (x29._super[0]._super * Val(56229));
  Val x93 = (x29._super[1]._super * Val(32195));
  Val x94 = (x29._super[2]._super * Val(41420));
  Val x95 = (x29._super[3]._super * Val(32711));
  Val x96 = (x29._super[4]._super * Val(3347));
  Val x97 = (x29._super[5]._super * Val(20899));
  Val x98 = (x29._super[6]._super * Val(48309));
  Val x99 = (x29._super[7]._super * Val(520));
  Val x100 = (((x92 + x93) + x94) + x95);
  Val x101 = (((x100 + x96) + x97) + x98);
  Val x102 = (x29._super[0]._super * Val(59829));
  Val x103 = (x29._super[1]._super * Val(21772));
  Val x104 = (x29._super[2]._super * Val(9228));
  Val x105 = (x29._super[3]._super * Val(48985));
  Val x106 = (x29._super[4]._super * Val(21304));
  Val x107 = (x29._super[5]._super * Val(51052));
  Val x108 = (x29._super[6]._super * Val(13488));
  Val x109 = (x29._super[7]._super * Val(36039));
  Val x110 = (((x102 + x103) + x104) + x105);
  Val x111 = (((x110 + x106) + x107) + x108);
  Val x112 = (x29._super[0]._super * Val(49755));
  Val x113 = (x29._super[1]._super * Val(23924));
  Val x114 = (x29._super[2]._super * Val(11375));
  Val x115 = (x29._super[3]._super * Val(3059));
  Val x116 = (x29._super[4]._super * Val(29524));
  Val x117 = (x29._super[5]._super * Val(59417));
  Val x118 = (x29._super[6]._super * Val(3251));
  Val x119 = (x29._super[7]._super * Val(65530));
  Val x120 = (((x112 + x113) + x114) + x115);
  Val x121 = (((x120 + x116) + x117) + x118);
  Val x122 = (x29._super[0]._super * Val(14678));
  Val x123 = (x29._super[1]._super * Val(29374));
  Val x124 = (x29._super[2]._super * Val(11753));
  Val x125 = (x29._super[3]._super * Val(50912));
  Val x126 = (x29._super[4]._super * Val(25866));
  Val x127 = (x29._super[5]._super * Val(53650));
  Val x128 = (x29._super[6]._super * Val(14620));
  Val x129 = (x29._super[7]._super * Val(37054));
  Val x130 = (((x122 + x123) + x124) + x125);
  Val x131 = (((x130 + x126) + x127) + x128);
  Val x132 = (x29._super[0]._super * Val(4593));
  Val x133 = (x29._super[1]._super * Val(45566));
  Val x134 = (x29._super[2]._super * Val(33962));
  Val x135 = (x29._super[3]._super * Val(37191));
  Val x136 = (x29._super[4]._super * Val(2747));
  Val x137 = (x29._super[5]._super * Val(1572));
  Val x138 = (x29._super[6]._super * Val(43594));
  Val x139 = (x29._super[7]._super * Val(27883));
  Val x140 = (((x132 + x133) + x134) + x135);
  Val x141 = (((x140 + x136) + x137) + x138);
  Val x142 = (x29._super[0]._super * Val(23025));
  Val x143 = (x29._super[1]._super * Val(32990));
  Val x144 = (x29._super[2]._super * Val(19060));
  Val x145 = (x29._super[3]._super * Val(54695));
  Val x146 = (x29._super[4]._super * Val(30314));
  Val x147 = (x29._super[5]._super * Val(54937));
  Val x148 = (x29._super[6]._super * Val(20184));
  Val x149 = (x29._super[7]._super * Val(42064));
  Val x150 = (((x142 + x143) + x144) + x145);
  Val x151 = (((x150 + x146) + x147) + x148);
  Val x152 = (x29._super[0]._super * Val(33444));
  Val x153 = (x29._super[1]._super * Val(1703));
  Val x154 = (x29._super[2]._super * Val(43484));
  Val x155 = (x29._super[3]._super * Val(25425));
  Val x156 = (x29._super[4]._super * Val(51502));
  Val x157 = (x29._super[5]._super * Val(13701));
  Val x158 = (x29._super[6]._super * Val(51791));
  Val x159 = (x29._super[7]._super * Val(41975));
  Val x160 = (((x152 + x153) + x154) + x155);
  Val x161 = (((x160 + x156) + x157) + x158);
  Val x162 = (x29._super[0]._super * Val(37439));
  Val x163 = (x29._super[1]._super * Val(39900));
  Val x164 = (x29._super[2]._super * Val(23728));
  Val x165 = (x29._super[3]._super * Val(1738));
  Val x166 = (x29._super[4]._super * Val(33218));
  Val x167 = (x29._super[5]._super * Val(62478));
  Val x168 = (x29._super[6]._super * Val(23452));
  Val x169 = (x29._super[7]._super * Val(48889));
  Val x170 = (((x162 + x163) + x164) + x165);
  Val x171 = (((x170 + x166) + x167) + x168);
  Val x172 = (x29._super[0]._super * Val(24277));
  Val x173 = (x29._super[1]._super * Val(61812));
  Val x174 = (x29._super[2]._super * Val(35034));
  Val x175 = (x29._super[3]._super * Val(10599));
  Val x176 = (x29._super[4]._super * Val(11397));
  Val x177 = (x29._super[5]._super * Val(41072));
  Val x178 = (x29._super[6]._super * Val(28659));
  Val x179 = (x29._super[7]._super * Val(30962));
  Val x180 = (((x172 + x173) + x174) + x175);
  Val x181 = (((x180 + x176) + x177) + x178);
  Val x182 = (x29._super[0]._super * Val(43804));
  Val x183 = (x29._super[1]._super * Val(49563));
  Val x184 = (x29._super[2]._super * Val(30457));
  Val x185 = (x29._super[3]._super * Val(5161));
  Val x186 = (x29._super[4]._super * Val(37490));
  Val x187 = (x29._super[5]._super * Val(4202));
  Val x188 = (x29._super[6]._super * Val(26670));
  Val x189 = (x29._super[7]._super * Val(50801));
  Val x190 = (((x182 + x183) + x184) + x185);
  Val x191 = (((x190 + x186) + x187) + x188);
  // ShaCycle(zirgen/circuit/keccak2/top.zir:186)
  Val100Array x192 = Val100Array{
      arg0.kflat[0]._super._super,  arg0.kflat[1]._super._super,  arg0.kflat[2]._super._super,
      arg0.kflat[3]._super._super,  arg0.kflat[4]._super._super,  arg0.kflat[5]._super._super,
      arg0.kflat[6]._super._super,  arg0.kflat[7]._super._super,  arg0.kflat[8]._super._super,
      arg0.kflat[9]._super._super,  arg0.kflat[10]._super._super, arg0.kflat[11]._super._super,
      arg0.kflat[12]._super._super, arg0.kflat[13]._super._super, arg0.kflat[14]._super._super,
      arg0.kflat[15]._super._super, arg0.kflat[16]._super._super, arg0.kflat[17]._super._super,
      arg0.kflat[18]._super._super, arg0.kflat[19]._super._super, arg0.kflat[20]._super._super,
      arg0.kflat[21]._super._super, arg0.kflat[22]._super._super, arg0.kflat[23]._super._super,
      arg0.kflat[24]._super._super, arg0.kflat[25]._super._super, arg0.kflat[26]._super._super,
      arg0.kflat[27]._super._super, arg0.kflat[28]._super._super, arg0.kflat[29]._super._super,
      arg0.kflat[30]._super._super, arg0.kflat[31]._super._super, arg0.kflat[32]._super._super,
      arg0.kflat[33]._super._super, arg0.kflat[34]._super._super, arg0.kflat[35]._super._super,
      arg0.kflat[36]._super._super, arg0.kflat[37]._super._super, arg0.kflat[38]._super._super,
      arg0.kflat[39]._super._super, arg0.kflat[40]._super._super, arg0.kflat[41]._super._super,
      arg0.kflat[42]._super._super, arg0.kflat[43]._super._super, arg0.kflat[44]._super._super,
      arg0.kflat[45]._super._super, arg0.kflat[46]._super._super, arg0.kflat[47]._super._super,
      arg0.kflat[48]._super._super, arg0.kflat[49]._super._super, arg0.kflat[50]._super._super,
      arg0.kflat[51]._super._super, arg0.kflat[52]._super._super, arg0.kflat[53]._super._super,
      arg0.kflat[54]._super._super, arg0.kflat[55]._super._super, arg0.kflat[56]._super._super,
      arg0.kflat[57]._super._super, arg0.kflat[58]._super._super, arg0.kflat[59]._super._super,
      arg0.kflat[60]._super._super, arg0.kflat[61]._super._super, arg0.kflat[62]._super._super,
      arg0.kflat[63]._super._super, arg0.kflat[64]._super._super, arg0.kflat[65]._super._super,
      arg0.kflat[66]._super._super, arg0.kflat[67]._super._super, arg0.kflat[68]._super._super,
      arg0.kflat[69]._super._super, arg0.kflat[70]._super._super, arg0.kflat[71]._super._super,
      arg0.kflat[72]._super._super, arg0.kflat[73]._super._super, arg0.kflat[74]._super._super,
      arg0.kflat[75]._super._super, arg0.kflat[76]._super._super, arg0.kflat[77]._super._super,
      arg0.kflat[78]._super._super, arg0.kflat[79]._super._super, arg0.kflat[80]._super._super,
      arg0.kflat[81]._super._super, arg0.kflat[82]._super._super, arg0.kflat[83]._super._super,
      arg0.kflat[84]._super._super, arg0.kflat[85]._super._super, arg0.kflat[86]._super._super,
      arg0.kflat[87]._super._super, arg0.kflat[88]._super._super, arg0.kflat[89]._super._super,
      arg0.kflat[90]._super._super, arg0.kflat[91]._super._super, arg0.kflat[92]._super._super,
      arg0.kflat[93]._super._super, arg0.kflat[94]._super._super, arg0.kflat[95]._super._super,
      arg0.kflat[96]._super._super, arg0.kflat[97]._super._super, arg0.kflat[98]._super._super,
      arg0.kflat[99]._super._super};
  // ShaCycle(zirgen/circuit/keccak2/top.zir:193)
  LoadWinStruct x193 = exec_LoadWin(ctx, x192, x29, arg3, LAYOUT_LOOKUP(layout4, win));
  // ShaCycle(zirgen/circuit/keccak2/top.zir:194)
  DoShaStepStruct x194 = exec_DoShaStep(
      ctx,
      ShaStateStruct{
          .a = Val32Array4Array{x5, x6, x7, x8},
          .e = Val32Array4Array{x9, x10, x11, x12},
          .w =
              Val32Array16Array{
                  x13, x14, x15, x16, x17, x18, x19, x20, x21, x22, x23, x24, x25, x26, x27, x28}},
      Val2Array{(x41 + x39), (x51 + x49)},
      x31._super,
      x193._super[0],
      LAYOUT_LOOKUP(layout4, step0));
  // ShaCycle(zirgen/circuit/keccak2/top.zir:195)
  DoShaStepStruct x195 = exec_DoShaStep(ctx,
                                        x194.newState,
                                        Val2Array{(x61 + x59), (x71 + x69)},
                                        x31._super,
                                        x193._super[1],
                                        LAYOUT_LOOKUP(layout4, step1));
  // ShaCycle(zirgen/circuit/keccak2/top.zir:196)
  DoShaStepStruct x196 = exec_DoShaStep(ctx,
                                        x195.newState,
                                        Val2Array{(x81 + x79), (x91 + x89)},
                                        x31._super,
                                        x193._super[2],
                                        LAYOUT_LOOKUP(layout4, step2));
  // ShaCycle(zirgen/circuit/keccak2/top.zir:197)
  DoShaStepStruct x197 = exec_DoShaStep(ctx,
                                        x196.newState,
                                        Val2Array{(x101 + x99), (x111 + x109)},
                                        x31._super,
                                        x193._super[3],
                                        LAYOUT_LOOKUP(layout4, step3));
  // ShaCycle(zirgen/circuit/keccak2/top.zir:198)
  DoShaStepStruct x198 = exec_DoShaStep(ctx,
                                        x197.newState,
                                        Val2Array{(x121 + x119), (x131 + x129)},
                                        x31._super,
                                        x193._super[4],
                                        LAYOUT_LOOKUP(layout4, step4));
  // ShaCycle(zirgen/circuit/keccak2/top.zir:199)
  DoShaStepStruct x199 = exec_DoShaStep(ctx,
                                        x198.newState,
                                        Val2Array{(x141 + x139), (x151 + x149)},
                                        x31._super,
                                        x193._super[5],
                                        LAYOUT_LOOKUP(layout4, step5));
  // ShaCycle(zirgen/circuit/keccak2/top.zir:200)
  DoShaStepStruct x200 = exec_DoShaStep(ctx,
                                        x199.newState,
                                        Val2Array{(x161 + x159), (x171 + x169)},
                                        x31._super,
                                        x193._super[6],
                                        LAYOUT_LOOKUP(layout4, step6));
  // ShaCycle(zirgen/circuit/keccak2/top.zir:201)
  DoShaStepStruct x201 = exec_DoShaStep(ctx,
                                        x200.newState,
                                        Val2Array{(x181 + x179), (x191 + x189)},
                                        x31._super,
                                        x193._super[7],
                                        LAYOUT_LOOKUP(layout4, step7));
  // ShaCycle(zirgen/circuit/keccak2/top.zir:203)
  Val800Array x202 = Val800Array{x194.a._super[0]._super._super,
                                 x194.a._super[1]._super._super,
                                 x194.a._super[2]._super._super,
                                 x194.a._super[3]._super._super,
                                 x194.a._super[4]._super._super,
                                 x194.a._super[5]._super._super,
                                 x194.a._super[6]._super._super,
                                 x194.a._super[7]._super._super,
                                 x194.a._super[8]._super._super,
                                 x194.a._super[9]._super._super,
                                 x194.a._super[10]._super._super,
                                 x194.a._super[11]._super._super,
                                 x194.a._super[12]._super._super,
                                 x194.a._super[13]._super._super,
                                 x194.a._super[14]._super._super,
                                 x194.a._super[15]._super._super,
                                 x194.a._super[16]._super._super,
                                 x194.a._super[17]._super._super,
                                 x194.a._super[18]._super._super,
                                 x194.a._super[19]._super._super,
                                 x194.a._super[20]._super._super,
                                 x194.a._super[21]._super._super,
                                 x194.a._super[22]._super._super,
                                 x194.a._super[23]._super._super,
                                 x194.a._super[24]._super._super,
                                 x194.a._super[25]._super._super,
                                 x194.a._super[26]._super._super,
                                 x194.a._super[27]._super._super,
                                 x194.a._super[28]._super._super,
                                 x194.a._super[29]._super._super,
                                 x194.a._super[30]._super._super,
                                 x194.a._super[31]._super._super,
                                 x195.a._super[0]._super._super,
                                 x195.a._super[1]._super._super,
                                 x195.a._super[2]._super._super,
                                 x195.a._super[3]._super._super,
                                 x195.a._super[4]._super._super,
                                 x195.a._super[5]._super._super,
                                 x195.a._super[6]._super._super,
                                 x195.a._super[7]._super._super,
                                 x195.a._super[8]._super._super,
                                 x195.a._super[9]._super._super,
                                 x195.a._super[10]._super._super,
                                 x195.a._super[11]._super._super,
                                 x195.a._super[12]._super._super,
                                 x195.a._super[13]._super._super,
                                 x195.a._super[14]._super._super,
                                 x195.a._super[15]._super._super,
                                 x195.a._super[16]._super._super,
                                 x195.a._super[17]._super._super,
                                 x195.a._super[18]._super._super,
                                 x195.a._super[19]._super._super,
                                 x195.a._super[20]._super._super,
                                 x195.a._super[21]._super._super,
                                 x195.a._super[22]._super._super,
                                 x195.a._super[23]._super._super,
                                 x195.a._super[24]._super._super,
                                 x195.a._super[25]._super._super,
                                 x195.a._super[26]._super._super,
                                 x195.a._super[27]._super._super,
                                 x195.a._super[28]._super._super,
                                 x195.a._super[29]._super._super,
                                 x195.a._super[30]._super._super,
                                 x195.a._super[31]._super._super,
                                 x196.a._super[0]._super._super,
                                 x196.a._super[1]._super._super,
                                 x196.a._super[2]._super._super,
                                 x196.a._super[3]._super._super,
                                 x196.a._super[4]._super._super,
                                 x196.a._super[5]._super._super,
                                 x196.a._super[6]._super._super,
                                 x196.a._super[7]._super._super,
                                 x196.a._super[8]._super._super,
                                 x196.a._super[9]._super._super,
                                 x196.a._super[10]._super._super,
                                 x196.a._super[11]._super._super,
                                 x196.a._super[12]._super._super,
                                 x196.a._super[13]._super._super,
                                 x196.a._super[14]._super._super,
                                 x196.a._super[15]._super._super,
                                 x196.a._super[16]._super._super,
                                 x196.a._super[17]._super._super,
                                 x196.a._super[18]._super._super,
                                 x196.a._super[19]._super._super,
                                 x196.a._super[20]._super._super,
                                 x196.a._super[21]._super._super,
                                 x196.a._super[22]._super._super,
                                 x196.a._super[23]._super._super,
                                 x196.a._super[24]._super._super,
                                 x196.a._super[25]._super._super,
                                 x196.a._super[26]._super._super,
                                 x196.a._super[27]._super._super,
                                 x196.a._super[28]._super._super,
                                 x196.a._super[29]._super._super,
                                 x196.a._super[30]._super._super,
                                 x196.a._super[31]._super._super,
                                 x197.a._super[0]._super._super,
                                 x197.a._super[1]._super._super,
                                 x197.a._super[2]._super._super,
                                 x197.a._super[3]._super._super,
                                 x197.a._super[4]._super._super,
                                 x197.a._super[5]._super._super,
                                 x197.a._super[6]._super._super,
                                 x197.a._super[7]._super._super,
                                 x197.a._super[8]._super._super,
                                 x197.a._super[9]._super._super,
                                 x197.a._super[10]._super._super,
                                 x197.a._super[11]._super._super,
                                 x197.a._super[12]._super._super,
                                 x197.a._super[13]._super._super,
                                 x197.a._super[14]._super._super,
                                 x197.a._super[15]._super._super,
                                 x197.a._super[16]._super._super,
                                 x197.a._super[17]._super._super,
                                 x197.a._super[18]._super._super,
                                 x197.a._super[19]._super._super,
                                 x197.a._super[20]._super._super,
                                 x197.a._super[21]._super._super,
                                 x197.a._super[22]._super._super,
                                 x197.a._super[23]._super._super,
                                 x197.a._super[24]._super._super,
                                 x197.a._super[25]._super._super,
                                 x197.a._super[26]._super._super,
                                 x197.a._super[27]._super._super,
                                 x197.a._super[28]._super._super,
                                 x197.a._super[29]._super._super,
                                 x197.a._super[30]._super._super,
                                 x197.a._super[31]._super._super,
                                 x198.a._super[0]._super._super,
                                 x198.a._super[1]._super._super,
                                 x198.a._super[2]._super._super,
                                 x198.a._super[3]._super._super,
                                 x198.a._super[4]._super._super,
                                 x198.a._super[5]._super._super,
                                 x198.a._super[6]._super._super,
                                 x198.a._super[7]._super._super,
                                 x198.a._super[8]._super._super,
                                 x198.a._super[9]._super._super,
                                 x198.a._super[10]._super._super,
                                 x198.a._super[11]._super._super,
                                 x198.a._super[12]._super._super,
                                 x198.a._super[13]._super._super,
                                 x198.a._super[14]._super._super,
                                 x198.a._super[15]._super._super,
                                 x198.a._super[16]._super._super,
                                 x198.a._super[17]._super._super,
                                 x198.a._super[18]._super._super,
                                 x198.a._super[19]._super._super,
                                 x198.a._super[20]._super._super,
                                 x198.a._super[21]._super._super,
                                 x198.a._super[22]._super._super,
                                 x198.a._super[23]._super._super,
                                 x198.a._super[24]._super._super,
                                 x198.a._super[25]._super._super,
                                 x198.a._super[26]._super._super,
                                 x198.a._super[27]._super._super,
                                 x198.a._super[28]._super._super,
                                 x198.a._super[29]._super._super,
                                 x198.a._super[30]._super._super,
                                 x198.a._super[31]._super._super,
                                 x199.a._super[0]._super._super,
                                 x199.a._super[1]._super._super,
                                 x199.a._super[2]._super._super,
                                 x199.a._super[3]._super._super,
                                 x199.a._super[4]._super._super,
                                 x199.a._super[5]._super._super,
                                 x199.a._super[6]._super._super,
                                 x199.a._super[7]._super._super,
                                 x199.a._super[8]._super._super,
                                 x199.a._super[9]._super._super,
                                 x199.a._super[10]._super._super,
                                 x199.a._super[11]._super._super,
                                 x199.a._super[12]._super._super,
                                 x199.a._super[13]._super._super,
                                 x199.a._super[14]._super._super,
                                 x199.a._super[15]._super._super,
                                 x199.a._super[16]._super._super,
                                 x199.a._super[17]._super._super,
                                 x199.a._super[18]._super._super,
                                 x199.a._super[19]._super._super,
                                 x199.a._super[20]._super._super,
                                 x199.a._super[21]._super._super,
                                 x199.a._super[22]._super._super,
                                 x199.a._super[23]._super._super,
                                 x199.a._super[24]._super._super,
                                 x199.a._super[25]._super._super,
                                 x199.a._super[26]._super._super,
                                 x199.a._super[27]._super._super,
                                 x199.a._super[28]._super._super,
                                 x199.a._super[29]._super._super,
                                 x199.a._super[30]._super._super,
                                 x199.a._super[31]._super._super,
                                 x200.a._super[0]._super._super,
                                 x200.a._super[1]._super._super,
                                 x200.a._super[2]._super._super,
                                 x200.a._super[3]._super._super,
                                 x200.a._super[4]._super._super,
                                 x200.a._super[5]._super._super,
                                 x200.a._super[6]._super._super,
                                 x200.a._super[7]._super._super,
                                 x200.a._super[8]._super._super,
                                 x200.a._super[9]._super._super,
                                 x200.a._super[10]._super._super,
                                 x200.a._super[11]._super._super,
                                 x200.a._super[12]._super._super,
                                 x200.a._super[13]._super._super,
                                 x200.a._super[14]._super._super,
                                 x200.a._super[15]._super._super,
                                 x200.a._super[16]._super._super,
                                 x200.a._super[17]._super._super,
                                 x200.a._super[18]._super._super,
                                 x200.a._super[19]._super._super,
                                 x200.a._super[20]._super._super,
                                 x200.a._super[21]._super._super,
                                 x200.a._super[22]._super._super,
                                 x200.a._super[23]._super._super,
                                 x200.a._super[24]._super._super,
                                 x200.a._super[25]._super._super,
                                 x200.a._super[26]._super._super,
                                 x200.a._super[27]._super._super,
                                 x200.a._super[28]._super._super,
                                 x200.a._super[29]._super._super,
                                 x200.a._super[30]._super._super,
                                 x200.a._super[31]._super._super,
                                 x201.a._super[0]._super._super,
                                 x201.a._super[1]._super._super,
                                 x201.a._super[2]._super._super,
                                 x201.a._super[3]._super._super,
                                 x201.a._super[4]._super._super,
                                 x201.a._super[5]._super._super,
                                 x201.a._super[6]._super._super,
                                 x201.a._super[7]._super._super,
                                 x201.a._super[8]._super._super,
                                 x201.a._super[9]._super._super,
                                 x201.a._super[10]._super._super,
                                 x201.a._super[11]._super._super,
                                 x201.a._super[12]._super._super,
                                 x201.a._super[13]._super._super,
                                 x201.a._super[14]._super._super,
                                 x201.a._super[15]._super._super,
                                 x201.a._super[16]._super._super,
                                 x201.a._super[17]._super._super,
                                 x201.a._super[18]._super._super,
                                 x201.a._super[19]._super._super,
                                 x201.a._super[20]._super._super,
                                 x201.a._super[21]._super._super,
                                 x201.a._super[22]._super._super,
                                 x201.a._super[23]._super._super,
                                 x201.a._super[24]._super._super,
                                 x201.a._super[25]._super._super,
                                 x201.a._super[26]._super._super,
                                 x201.a._super[27]._super._super,
                                 x201.a._super[28]._super._super,
                                 x201.a._super[29]._super._super,
                                 x201.a._super[30]._super._super,
                                 x201.a._super[31]._super._super,
                                 x194.e._super[0]._super._super,
                                 x194.e._super[1]._super._super,
                                 x194.e._super[2]._super._super,
                                 x194.e._super[3]._super._super,
                                 x194.e._super[4]._super._super,
                                 x194.e._super[5]._super._super,
                                 x194.e._super[6]._super._super,
                                 x194.e._super[7]._super._super,
                                 x194.e._super[8]._super._super,
                                 x194.e._super[9]._super._super,
                                 x194.e._super[10]._super._super,
                                 x194.e._super[11]._super._super,
                                 x194.e._super[12]._super._super,
                                 x194.e._super[13]._super._super,
                                 x194.e._super[14]._super._super,
                                 x194.e._super[15]._super._super,
                                 x194.e._super[16]._super._super,
                                 x194.e._super[17]._super._super,
                                 x194.e._super[18]._super._super,
                                 x194.e._super[19]._super._super,
                                 x194.e._super[20]._super._super,
                                 x194.e._super[21]._super._super,
                                 x194.e._super[22]._super._super,
                                 x194.e._super[23]._super._super,
                                 x194.e._super[24]._super._super,
                                 x194.e._super[25]._super._super,
                                 x194.e._super[26]._super._super,
                                 x194.e._super[27]._super._super,
                                 x194.e._super[28]._super._super,
                                 x194.e._super[29]._super._super,
                                 x194.e._super[30]._super._super,
                                 x194.e._super[31]._super._super,
                                 x195.e._super[0]._super._super,
                                 x195.e._super[1]._super._super,
                                 x195.e._super[2]._super._super,
                                 x195.e._super[3]._super._super,
                                 x195.e._super[4]._super._super,
                                 x195.e._super[5]._super._super,
                                 x195.e._super[6]._super._super,
                                 x195.e._super[7]._super._super,
                                 x195.e._super[8]._super._super,
                                 x195.e._super[9]._super._super,
                                 x195.e._super[10]._super._super,
                                 x195.e._super[11]._super._super,
                                 x195.e._super[12]._super._super,
                                 x195.e._super[13]._super._super,
                                 x195.e._super[14]._super._super,
                                 x195.e._super[15]._super._super,
                                 x195.e._super[16]._super._super,
                                 x195.e._super[17]._super._super,
                                 x195.e._super[18]._super._super,
                                 x195.e._super[19]._super._super,
                                 x195.e._super[20]._super._super,
                                 x195.e._super[21]._super._super,
                                 x195.e._super[22]._super._super,
                                 x195.e._super[23]._super._super,
                                 x195.e._super[24]._super._super,
                                 x195.e._super[25]._super._super,
                                 x195.e._super[26]._super._super,
                                 x195.e._super[27]._super._super,
                                 x195.e._super[28]._super._super,
                                 x195.e._super[29]._super._super,
                                 x195.e._super[30]._super._super,
                                 x195.e._super[31]._super._super,
                                 x196.e._super[0]._super._super,
                                 x196.e._super[1]._super._super,
                                 x196.e._super[2]._super._super,
                                 x196.e._super[3]._super._super,
                                 x196.e._super[4]._super._super,
                                 x196.e._super[5]._super._super,
                                 x196.e._super[6]._super._super,
                                 x196.e._super[7]._super._super,
                                 x196.e._super[8]._super._super,
                                 x196.e._super[9]._super._super,
                                 x196.e._super[10]._super._super,
                                 x196.e._super[11]._super._super,
                                 x196.e._super[12]._super._super,
                                 x196.e._super[13]._super._super,
                                 x196.e._super[14]._super._super,
                                 x196.e._super[15]._super._super,
                                 x196.e._super[16]._super._super,
                                 x196.e._super[17]._super._super,
                                 x196.e._super[18]._super._super,
                                 x196.e._super[19]._super._super,
                                 x196.e._super[20]._super._super,
                                 x196.e._super[21]._super._super,
                                 x196.e._super[22]._super._super,
                                 x196.e._super[23]._super._super,
                                 x196.e._super[24]._super._super,
                                 x196.e._super[25]._super._super,
                                 x196.e._super[26]._super._super,
                                 x196.e._super[27]._super._super,
                                 x196.e._super[28]._super._super,
                                 x196.e._super[29]._super._super,
                                 x196.e._super[30]._super._super,
                                 x196.e._super[31]._super._super,
                                 x197.e._super[0]._super._super,
                                 x197.e._super[1]._super._super,
                                 x197.e._super[2]._super._super,
                                 x197.e._super[3]._super._super,
                                 x197.e._super[4]._super._super,
                                 x197.e._super[5]._super._super,
                                 x197.e._super[6]._super._super,
                                 x197.e._super[7]._super._super,
                                 x197.e._super[8]._super._super,
                                 x197.e._super[9]._super._super,
                                 x197.e._super[10]._super._super,
                                 x197.e._super[11]._super._super,
                                 x197.e._super[12]._super._super,
                                 x197.e._super[13]._super._super,
                                 x197.e._super[14]._super._super,
                                 x197.e._super[15]._super._super,
                                 x197.e._super[16]._super._super,
                                 x197.e._super[17]._super._super,
                                 x197.e._super[18]._super._super,
                                 x197.e._super[19]._super._super,
                                 x197.e._super[20]._super._super,
                                 x197.e._super[21]._super._super,
                                 x197.e._super[22]._super._super,
                                 x197.e._super[23]._super._super,
                                 x197.e._super[24]._super._super,
                                 x197.e._super[25]._super._super,
                                 x197.e._super[26]._super._super,
                                 x197.e._super[27]._super._super,
                                 x197.e._super[28]._super._super,
                                 x197.e._super[29]._super._super,
                                 x197.e._super[30]._super._super,
                                 x197.e._super[31]._super._super,
                                 x198.e._super[0]._super._super,
                                 x198.e._super[1]._super._super,
                                 x198.e._super[2]._super._super,
                                 x198.e._super[3]._super._super,
                                 x198.e._super[4]._super._super,
                                 x198.e._super[5]._super._super,
                                 x198.e._super[6]._super._super,
                                 x198.e._super[7]._super._super,
                                 x198.e._super[8]._super._super,
                                 x198.e._super[9]._super._super,
                                 x198.e._super[10]._super._super,
                                 x198.e._super[11]._super._super,
                                 x198.e._super[12]._super._super,
                                 x198.e._super[13]._super._super,
                                 x198.e._super[14]._super._super,
                                 x198.e._super[15]._super._super,
                                 x198.e._super[16]._super._super,
                                 x198.e._super[17]._super._super,
                                 x198.e._super[18]._super._super,
                                 x198.e._super[19]._super._super,
                                 x198.e._super[20]._super._super,
                                 x198.e._super[21]._super._super,
                                 x198.e._super[22]._super._super,
                                 x198.e._super[23]._super._super,
                                 x198.e._super[24]._super._super,
                                 x198.e._super[25]._super._super,
                                 x198.e._super[26]._super._super,
                                 x198.e._super[27]._super._super,
                                 x198.e._super[28]._super._super,
                                 x198.e._super[29]._super._super,
                                 x198.e._super[30]._super._super,
                                 x198.e._super[31]._super._super,
                                 x199.e._super[0]._super._super,
                                 x199.e._super[1]._super._super,
                                 x199.e._super[2]._super._super,
                                 x199.e._super[3]._super._super,
                                 x199.e._super[4]._super._super,
                                 x199.e._super[5]._super._super,
                                 x199.e._super[6]._super._super,
                                 x199.e._super[7]._super._super,
                                 x199.e._super[8]._super._super,
                                 x199.e._super[9]._super._super,
                                 x199.e._super[10]._super._super,
                                 x199.e._super[11]._super._super,
                                 x199.e._super[12]._super._super,
                                 x199.e._super[13]._super._super,
                                 x199.e._super[14]._super._super,
                                 x199.e._super[15]._super._super,
                                 x199.e._super[16]._super._super,
                                 x199.e._super[17]._super._super,
                                 x199.e._super[18]._super._super,
                                 x199.e._super[19]._super._super,
                                 x199.e._super[20]._super._super,
                                 x199.e._super[21]._super._super,
                                 x199.e._super[22]._super._super,
                                 x199.e._super[23]._super._super,
                                 x199.e._super[24]._super._super,
                                 x199.e._super[25]._super._super,
                                 x199.e._super[26]._super._super,
                                 x199.e._super[27]._super._super,
                                 x199.e._super[28]._super._super,
                                 x199.e._super[29]._super._super,
                                 x199.e._super[30]._super._super,
                                 x199.e._super[31]._super._super,
                                 x200.e._super[0]._super._super,
                                 x200.e._super[1]._super._super,
                                 x200.e._super[2]._super._super,
                                 x200.e._super[3]._super._super,
                                 x200.e._super[4]._super._super,
                                 x200.e._super[5]._super._super,
                                 x200.e._super[6]._super._super,
                                 x200.e._super[7]._super._super,
                                 x200.e._super[8]._super._super,
                                 x200.e._super[9]._super._super,
                                 x200.e._super[10]._super._super,
                                 x200.e._super[11]._super._super,
                                 x200.e._super[12]._super._super,
                                 x200.e._super[13]._super._super,
                                 x200.e._super[14]._super._super,
                                 x200.e._super[15]._super._super,
                                 x200.e._super[16]._super._super,
                                 x200.e._super[17]._super._super,
                                 x200.e._super[18]._super._super,
                                 x200.e._super[19]._super._super,
                                 x200.e._super[20]._super._super,
                                 x200.e._super[21]._super._super,
                                 x200.e._super[22]._super._super,
                                 x200.e._super[23]._super._super,
                                 x200.e._super[24]._super._super,
                                 x200.e._super[25]._super._super,
                                 x200.e._super[26]._super._super,
                                 x200.e._super[27]._super._super,
                                 x200.e._super[28]._super._super,
                                 x200.e._super[29]._super._super,
                                 x200.e._super[30]._super._super,
                                 x200.e._super[31]._super._super,
                                 x201.e._super[0]._super._super,
                                 x201.e._super[1]._super._super,
                                 x201.e._super[2]._super._super,
                                 x201.e._super[3]._super._super,
                                 x201.e._super[4]._super._super,
                                 x201.e._super[5]._super._super,
                                 x201.e._super[6]._super._super,
                                 x201.e._super[7]._super._super,
                                 x201.e._super[8]._super._super,
                                 x201.e._super[9]._super._super,
                                 x201.e._super[10]._super._super,
                                 x201.e._super[11]._super._super,
                                 x201.e._super[12]._super._super,
                                 x201.e._super[13]._super._super,
                                 x201.e._super[14]._super._super,
                                 x201.e._super[15]._super._super,
                                 x201.e._super[16]._super._super,
                                 x201.e._super[17]._super._super,
                                 x201.e._super[18]._super._super,
                                 x201.e._super[19]._super._super,
                                 x201.e._super[20]._super._super,
                                 x201.e._super[21]._super._super,
                                 x201.e._super[22]._super._super,
                                 x201.e._super[23]._super._super,
                                 x201.e._super[24]._super._super,
                                 x201.e._super[25]._super._super,
                                 x201.e._super[26]._super._super,
                                 x201.e._super[27]._super._super,
                                 x201.e._super[28]._super._super,
                                 x201.e._super[29]._super._super,
                                 x201.e._super[30]._super._super,
                                 x201.e._super[31]._super._super,
                                 x194.w._super[0]._super._super,
                                 x194.w._super[1]._super._super,
                                 x194.w._super[2]._super._super,
                                 x194.w._super[3]._super._super,
                                 x194.w._super[4]._super._super,
                                 x194.w._super[5]._super._super,
                                 x194.w._super[6]._super._super,
                                 x194.w._super[7]._super._super,
                                 x194.w._super[8]._super._super,
                                 x194.w._super[9]._super._super,
                                 x194.w._super[10]._super._super,
                                 x194.w._super[11]._super._super,
                                 x194.w._super[12]._super._super,
                                 x194.w._super[13]._super._super,
                                 x194.w._super[14]._super._super,
                                 x194.w._super[15]._super._super,
                                 x194.w._super[16]._super._super,
                                 x194.w._super[17]._super._super,
                                 x194.w._super[18]._super._super,
                                 x194.w._super[19]._super._super,
                                 x194.w._super[20]._super._super,
                                 x194.w._super[21]._super._super,
                                 x194.w._super[22]._super._super,
                                 x194.w._super[23]._super._super,
                                 x194.w._super[24]._super._super,
                                 x194.w._super[25]._super._super,
                                 x194.w._super[26]._super._super,
                                 x194.w._super[27]._super._super,
                                 x194.w._super[28]._super._super,
                                 x194.w._super[29]._super._super,
                                 x194.w._super[30]._super._super,
                                 x194.w._super[31]._super._super,
                                 x195.w._super[0]._super._super,
                                 x195.w._super[1]._super._super,
                                 x195.w._super[2]._super._super,
                                 x195.w._super[3]._super._super,
                                 x195.w._super[4]._super._super,
                                 x195.w._super[5]._super._super,
                                 x195.w._super[6]._super._super,
                                 x195.w._super[7]._super._super,
                                 x195.w._super[8]._super._super,
                                 x195.w._super[9]._super._super,
                                 x195.w._super[10]._super._super,
                                 x195.w._super[11]._super._super,
                                 x195.w._super[12]._super._super,
                                 x195.w._super[13]._super._super,
                                 x195.w._super[14]._super._super,
                                 x195.w._super[15]._super._super,
                                 x195.w._super[16]._super._super,
                                 x195.w._super[17]._super._super,
                                 x195.w._super[18]._super._super,
                                 x195.w._super[19]._super._super,
                                 x195.w._super[20]._super._super,
                                 x195.w._super[21]._super._super,
                                 x195.w._super[22]._super._super,
                                 x195.w._super[23]._super._super,
                                 x195.w._super[24]._super._super,
                                 x195.w._super[25]._super._super,
                                 x195.w._super[26]._super._super,
                                 x195.w._super[27]._super._super,
                                 x195.w._super[28]._super._super,
                                 x195.w._super[29]._super._super,
                                 x195.w._super[30]._super._super,
                                 x195.w._super[31]._super._super,
                                 x196.w._super[0]._super._super,
                                 x196.w._super[1]._super._super,
                                 x196.w._super[2]._super._super,
                                 x196.w._super[3]._super._super,
                                 x196.w._super[4]._super._super,
                                 x196.w._super[5]._super._super,
                                 x196.w._super[6]._super._super,
                                 x196.w._super[7]._super._super,
                                 x196.w._super[8]._super._super,
                                 x196.w._super[9]._super._super,
                                 x196.w._super[10]._super._super,
                                 x196.w._super[11]._super._super,
                                 x196.w._super[12]._super._super,
                                 x196.w._super[13]._super._super,
                                 x196.w._super[14]._super._super,
                                 x196.w._super[15]._super._super,
                                 x196.w._super[16]._super._super,
                                 x196.w._super[17]._super._super,
                                 x196.w._super[18]._super._super,
                                 x196.w._super[19]._super._super,
                                 x196.w._super[20]._super._super,
                                 x196.w._super[21]._super._super,
                                 x196.w._super[22]._super._super,
                                 x196.w._super[23]._super._super,
                                 x196.w._super[24]._super._super,
                                 x196.w._super[25]._super._super,
                                 x196.w._super[26]._super._super,
                                 x196.w._super[27]._super._super,
                                 x196.w._super[28]._super._super,
                                 x196.w._super[29]._super._super,
                                 x196.w._super[30]._super._super,
                                 x196.w._super[31]._super._super,
                                 x197.w._super[0]._super._super,
                                 x197.w._super[1]._super._super,
                                 x197.w._super[2]._super._super,
                                 x197.w._super[3]._super._super,
                                 x197.w._super[4]._super._super,
                                 x197.w._super[5]._super._super,
                                 x197.w._super[6]._super._super,
                                 x197.w._super[7]._super._super,
                                 x197.w._super[8]._super._super,
                                 x197.w._super[9]._super._super,
                                 x197.w._super[10]._super._super,
                                 x197.w._super[11]._super._super,
                                 x197.w._super[12]._super._super,
                                 x197.w._super[13]._super._super,
                                 x197.w._super[14]._super._super,
                                 x197.w._super[15]._super._super,
                                 x197.w._super[16]._super._super,
                                 x197.w._super[17]._super._super,
                                 x197.w._super[18]._super._super,
                                 x197.w._super[19]._super._super,
                                 x197.w._super[20]._super._super,
                                 x197.w._super[21]._super._super,
                                 x197.w._super[22]._super._super,
                                 x197.w._super[23]._super._super,
                                 x197.w._super[24]._super._super,
                                 x197.w._super[25]._super._super,
                                 x197.w._super[26]._super._super,
                                 x197.w._super[27]._super._super,
                                 x197.w._super[28]._super._super,
                                 x197.w._super[29]._super._super,
                                 x197.w._super[30]._super._super,
                                 x197.w._super[31]._super._super,
                                 x198.w._super[0]._super._super,
                                 x198.w._super[1]._super._super,
                                 x198.w._super[2]._super._super,
                                 x198.w._super[3]._super._super,
                                 x198.w._super[4]._super._super,
                                 x198.w._super[5]._super._super,
                                 x198.w._super[6]._super._super,
                                 x198.w._super[7]._super._super,
                                 x198.w._super[8]._super._super,
                                 x198.w._super[9]._super._super,
                                 x198.w._super[10]._super._super,
                                 x198.w._super[11]._super._super,
                                 x198.w._super[12]._super._super,
                                 x198.w._super[13]._super._super,
                                 x198.w._super[14]._super._super,
                                 x198.w._super[15]._super._super,
                                 x198.w._super[16]._super._super,
                                 x198.w._super[17]._super._super,
                                 x198.w._super[18]._super._super,
                                 x198.w._super[19]._super._super,
                                 x198.w._super[20]._super._super,
                                 x198.w._super[21]._super._super,
                                 x198.w._super[22]._super._super,
                                 x198.w._super[23]._super._super,
                                 x198.w._super[24]._super._super,
                                 x198.w._super[25]._super._super,
                                 x198.w._super[26]._super._super,
                                 x198.w._super[27]._super._super,
                                 x198.w._super[28]._super._super,
                                 x198.w._super[29]._super._super,
                                 x198.w._super[30]._super._super,
                                 x198.w._super[31]._super._super,
                                 x199.w._super[0]._super._super,
                                 x199.w._super[1]._super._super,
                                 x199.w._super[2]._super._super,
                                 x199.w._super[3]._super._super,
                                 x199.w._super[4]._super._super,
                                 x199.w._super[5]._super._super,
                                 x199.w._super[6]._super._super,
                                 x199.w._super[7]._super._super,
                                 x199.w._super[8]._super._super,
                                 x199.w._super[9]._super._super,
                                 x199.w._super[10]._super._super,
                                 x199.w._super[11]._super._super,
                                 x199.w._super[12]._super._super,
                                 x199.w._super[13]._super._super,
                                 x199.w._super[14]._super._super,
                                 x199.w._super[15]._super._super,
                                 x199.w._super[16]._super._super,
                                 x199.w._super[17]._super._super,
                                 x199.w._super[18]._super._super,
                                 x199.w._super[19]._super._super,
                                 x199.w._super[20]._super._super,
                                 x199.w._super[21]._super._super,
                                 x199.w._super[22]._super._super,
                                 x199.w._super[23]._super._super,
                                 x199.w._super[24]._super._super,
                                 x199.w._super[25]._super._super,
                                 x199.w._super[26]._super._super,
                                 x199.w._super[27]._super._super,
                                 x199.w._super[28]._super._super,
                                 x199.w._super[29]._super._super,
                                 x199.w._super[30]._super._super,
                                 x199.w._super[31]._super._super,
                                 x200.w._super[0]._super._super,
                                 x200.w._super[1]._super._super,
                                 x200.w._super[2]._super._super,
                                 x200.w._super[3]._super._super,
                                 x200.w._super[4]._super._super,
                                 x200.w._super[5]._super._super,
                                 x200.w._super[6]._super._super,
                                 x200.w._super[7]._super._super,
                                 x200.w._super[8]._super._super,
                                 x200.w._super[9]._super._super,
                                 x200.w._super[10]._super._super,
                                 x200.w._super[11]._super._super,
                                 x200.w._super[12]._super._super,
                                 x200.w._super[13]._super._super,
                                 x200.w._super[14]._super._super,
                                 x200.w._super[15]._super._super,
                                 x200.w._super[16]._super._super,
                                 x200.w._super[17]._super._super,
                                 x200.w._super[18]._super._super,
                                 x200.w._super[19]._super._super,
                                 x200.w._super[20]._super._super,
                                 x200.w._super[21]._super._super,
                                 x200.w._super[22]._super._super,
                                 x200.w._super[23]._super._super,
                                 x200.w._super[24]._super._super,
                                 x200.w._super[25]._super._super,
                                 x200.w._super[26]._super._super,
                                 x200.w._super[27]._super._super,
                                 x200.w._super[28]._super._super,
                                 x200.w._super[29]._super._super,
                                 x200.w._super[30]._super._super,
                                 x200.w._super[31]._super._super,
                                 x201.w._super[0]._super._super,
                                 x201.w._super[1]._super._super,
                                 x201.w._super[2]._super._super,
                                 x201.w._super[3]._super._super,
                                 x201.w._super[4]._super._super,
                                 x201.w._super[5]._super._super,
                                 x201.w._super[6]._super._super,
                                 x201.w._super[7]._super._super,
                                 x201.w._super[8]._super._super,
                                 x201.w._super[9]._super._super,
                                 x201.w._super[10]._super._super,
                                 x201.w._super[11]._super._super,
                                 x201.w._super[12]._super._super,
                                 x201.w._super[13]._super._super,
                                 x201.w._super[14]._super._super,
                                 x201.w._super[15]._super._super,
                                 x201.w._super[16]._super._super,
                                 x201.w._super[17]._super._super,
                                 x201.w._super[18]._super._super,
                                 x201.w._super[19]._super._super,
                                 x201.w._super[20]._super._super,
                                 x201.w._super[21]._super._super,
                                 x201.w._super[22]._super._super,
                                 x201.w._super[23]._super._super,
                                 x201.w._super[24]._super._super,
                                 x201.w._super[25]._super._super,
                                 x201.w._super[26]._super._super,
                                 x201.w._super[27]._super._super,
                                 x201.w._super[28]._super._super,
                                 x201.w._super[29]._super._super,
                                 x201.w._super[30]._super._super,
                                 x201.w._super[31]._super._super,
                                 Val(0),
                                 Val(0),
                                 Val(0),
                                 Val(0),
                                 Val(0),
                                 Val(0),
                                 Val(0),
                                 Val(0),
                                 Val(0),
                                 Val(0),
                                 Val(0),
                                 Val(0),
                                 Val(0),
                                 Val(0),
                                 Val(0),
                                 Val(0),
                                 Val(0),
                                 Val(0),
                                 Val(0),
                                 Val(0),
                                 Val(0),
                                 Val(0),
                                 Val(0),
                                 Val(0),
                                 Val(0),
                                 Val(0),
                                 Val(0),
                                 Val(0),
                                 Val(0),
                                 Val(0),
                                 Val(0),
                                 Val(0)};
  // ShaCycle(zirgen/circuit/keccak2/top.zir:186)
  Val16Array x203 = Val16Array{arg0.sflat[0]._super,
                               arg0.sflat[1]._super,
                               arg0.sflat[2]._super,
                               arg0.sflat[3]._super,
                               arg0.sflat[4]._super,
                               arg0.sflat[5]._super,
                               arg0.sflat[6]._super,
                               arg0.sflat[7]._super,
                               arg0.sflat[8]._super,
                               arg0.sflat[9]._super,
                               arg0.sflat[10]._super,
                               arg0.sflat[11]._super,
                               arg0.sflat[12]._super,
                               arg0.sflat[13]._super,
                               arg0.sflat[14]._super,
                               arg0.sflat[15]._super};
  // ShaCycle(zirgen/circuit/keccak2/top.zir:208)
  TopStateStruct x204 = exec_TopState(ctx, x202, x192, x203, LAYOUT_LOOKUP(layout4, _super));
  return x204;
}
__device__ OneHot_12_Struct exec_OneHot_12_(ExecContext& ctx,
                                            Val arg0,
                                            BoundLayout<OneHot_12_Layout> layout1) {
  // OneHot(zirgen/circuit/keccak2/one_hot.zir:7)
  OneHot_12__SuperStruct12Array x2 = map(
      Val12Array{Val(0),
                 Val(1),
                 Val(2),
                 Val(3),
                 Val(4),
                 Val(5),
                 Val(6),
                 Val(7),
                 Val(8),
                 Val(9),
                 Val(10),
                 Val(11)},
      LAYOUT_LOOKUP(layout1, _super),
      ([&](Val12Array::value_type x3, BoundLayout<NondetRegLayout12LayoutArray::value_type> x4) {
        NondetRegStruct x5 = exec_NondetBitReg(ctx, isz((x3 - arg0)), x4);
        return OneHot_12__SuperStruct{._super = x5};
      }));
  // OneHot(zirgen/circuit/keccak2/one_hot.zir:9)
  Val x6 = (x2[0]._super._super + x2[1]._super._super);
  Val x7 = ((x6 + x2[2]._super._super) + x2[3]._super._super);
  Val x8 = ((x7 + x2[4]._super._super) + x2[5]._super._super);
  Val x9 = ((x8 + x2[6]._super._super) + x2[7]._super._super);
  Val x10 = ((x9 + x2[8]._super._super) + x2[9]._super._super);
  Val x11 = ((x10 + x2[10]._super._super) + x2[11]._super._super);
  EQZ((x11 - Val(1)), "OneHot(zirgen/circuit/keccak2/one_hot.zir:9)");
  // OneHot(zirgen/circuit/keccak2/one_hot.zir:11)
  Val x12 = (x2[2]._super._super * Val(2));
  Val x13 = (x2[3]._super._super * Val(3));
  Val x14 = (x2[4]._super._super * Val(4));
  Val x15 = (x2[5]._super._super * Val(5));
  Val x16 = (x2[6]._super._super * Val(6));
  Val x17 = (x2[7]._super._super * Val(7));
  Val x18 = (x2[8]._super._super * Val(8));
  Val x19 = (x2[9]._super._super * Val(9));
  Val x20 = (x2[10]._super._super * Val(10));
  Val x21 = (x2[11]._super._super * Val(11));
  Val x22 = (x2[1]._super._super + x12);
  Val x23 = (((x22 + x13) + x14) + x15);
  Val x24 = (((x23 + x16) + x17) + x18);
  Val x25 = (((x24 + x19) + x20) + x21);
  EQZ((x25 - arg0), "OneHot(zirgen/circuit/keccak2/one_hot.zir:11)");
  return OneHot_12_Struct{.bits = x2};
}

} // namespace risc0::circuit::keccak::cuda
