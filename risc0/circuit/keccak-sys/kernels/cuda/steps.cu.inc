
__device__ NondetRegStruct back_NondetReg(ExecContext& ctx,
                                          Index distance0,
                                          BoundLayout<NondetRegLayout> layout1) {
  NondetRegStruct x2 = NondetRegStruct{._super = LOAD(LAYOUT_LOOKUP(layout1, _super), distance0)};
  return x2;
}
__device__ NondetRegStruct exec_NondetReg(ExecContext& ctx,
                                          Val arg0,
                                          BoundLayout<NondetRegLayout> layout1) {
  BoundLayout<Reg> x2 = LAYOUT_LOOKUP(layout1, _super);
  STORE(x2, arg0);
  return NondetRegStruct{._super = LOAD(x2, 0)};
}
__device__ NondetRegStruct back_Reg(ExecContext& ctx,
                                    Index distance0,
                                    BoundLayout<NondetRegLayout> layout1) {
  // Reg(<preamble>:4)
  NondetRegStruct x2 = back_NondetReg(ctx, distance0, layout1);
  return x2;
}
__device__ NondetRegStruct exec_Reg(ExecContext& ctx,
                                    Val arg0,
                                    BoundLayout<NondetRegLayout> layout1) {
  NondetRegStruct x2 = exec_NondetReg(ctx, arg0, layout1);
  // Reg(<preamble>:5)
  EQZ((arg0 - x2._super), "Reg(<preamble>:5)");
  return x2;
}
__device__ NondetRegStruct exec_NondetBitReg(ExecContext& ctx,
                                             Val arg0,
                                             BoundLayout<NondetRegLayout> layout1) {
  // NondetBitReg(zirgen/circuit/keccak2/bits.zir:11)
  NondetRegStruct x2 = exec_NondetReg(ctx, arg0, layout1);
  Val x3 = x2._super;
  // AssertBit(zirgen/circuit/keccak2/bits.zir:6)
  // NondetBitReg(zirgen/circuit/keccak2/bits.zir:12)
  EQZ((x3 * (Val(1) - x3)),
      "loc(callsite( AssertBit ( zirgen/circuit/keccak2/bits.zir :6:20) at  NondetBitReg ( "
      "zirgen/circuit/keccak2/bits.zir :12:13)))");
  return x2;
}
__device__ NondetRegStruct exec_IsZero(ExecContext& ctx,
                                       Val arg0,
                                       BoundLayout<IsZeroLayout> layout1) {
  // IsZero(zirgen/circuit/keccak2/is_zero.zir:8)
  NondetRegStruct x2 = exec_NondetReg(ctx, isz(arg0), LAYOUT_LOOKUP(layout1, _super));
  // IsZero(zirgen/circuit/keccak2/is_zero.zir:11)
  NondetRegStruct x3 = exec_NondetReg(ctx, inv_0(arg0), LAYOUT_LOOKUP(layout1, inv));
  // IsZero(zirgen/circuit/keccak2/is_zero.zir:8)
  Val x4 = x2._super;
  // AssertBit(zirgen/circuit/keccak2/bits.zir:6)
  // IsZero(zirgen/circuit/keccak2/is_zero.zir:14)
  Val x5 = (Val(1) - x4);
  EQZ((x4 * x5),
      "loc(callsite( AssertBit ( zirgen/circuit/keccak2/bits.zir :6:20) at  IsZero ( "
      "zirgen/circuit/keccak2/is_zero.zir :14:13)))");
  // IsZero(zirgen/circuit/keccak2/is_zero.zir:11)
  Val x6 = x3._super;
  // IsZero(zirgen/circuit/keccak2/is_zero.zir:16)
  EQZ(((arg0 * x6) - x5), "IsZero(zirgen/circuit/keccak2/is_zero.zir:16)");
  // IsZero(zirgen/circuit/keccak2/is_zero.zir:18)
  EQZ((x4 * arg0), "IsZero(zirgen/circuit/keccak2/is_zero.zir:18)");
  // IsZero(zirgen/circuit/keccak2/is_zero.zir:20)
  EQZ((x4 * x6), "IsZero(zirgen/circuit/keccak2/is_zero.zir:20)");
  return x2;
}
__device__ NondetRegStruct exec_Xor5(ExecContext& ctx,
                                     Val5Array arg0,
                                     BoundLayout<NondetRegLayout> layout1) {
  // Xor5(zirgen/circuit/keccak2/xor5.zir:7)
  Val x2 = ((arg0[0] + arg0[1]) + arg0[2]);
  Val x3 = ((x2 + arg0[3]) + arg0[4]);
  // Xor5(zirgen/circuit/keccak2/xor5.zir:8)
  NondetRegStruct x4 = exec_NondetBitReg(ctx, bitAnd(x3, Val(1)), layout1);
  // Xor5(zirgen/circuit/keccak2/xor5.zir:9)
  Val x5 = (x3 - x4._super);
  // Xor5(zirgen/circuit/keccak2/xor5.zir:10)
  Val x6 = ((x5 * (Val(2) - x5)) * (Val(4) - x5));
  EQZ(x6, "Xor5(zirgen/circuit/keccak2/xor5.zir:10)");
  return x4;
}
__device__ ThetaP1Struct exec_ThetaP1(ExecContext& ctx,
                                      Val64Array5Array5Array arg0,
                                      BoundLayout<ThetaP1Layout> layout1) {
  // ThetaP1(zirgen/circuit/keccak2/keccak.zir:11)
  ThetaP1_Super_SuperStruct5Array x2 =
      map(Val5Array{Val(0), Val(1), Val(2), Val(3), Val(4)},
          LAYOUT_LOOKUP(layout1, _super),
          ([&](Val5Array::value_type x3,
               BoundLayout<ThetaP1_Super_SuperLayout5LayoutArray::value_type> x4) {
            // ThetaP1(zirgen/circuit/keccak2/keccak.zir:12)
            ThetaP1_Super_Super_SuperStruct64Array x5 = map(
                Val64Array{Val(0),  Val(1),  Val(2),  Val(3),  Val(4),  Val(5),  Val(6),  Val(7),
                           Val(8),  Val(9),  Val(10), Val(11), Val(12), Val(13), Val(14), Val(15),
                           Val(16), Val(17), Val(18), Val(19), Val(20), Val(21), Val(22), Val(23),
                           Val(24), Val(25), Val(26), Val(27), Val(28), Val(29), Val(30), Val(31),
                           Val(32), Val(33), Val(34), Val(35), Val(36), Val(37), Val(38), Val(39),
                           Val(40), Val(41), Val(42), Val(43), Val(44), Val(45), Val(46), Val(47),
                           Val(48), Val(49), Val(50), Val(51), Val(52), Val(53), Val(54), Val(55),
                           Val(56), Val(57), Val(58), Val(59), Val(60), Val(61), Val(62), Val(63)},
                LAYOUT_LOOKUP(x4, _super),
                ([&](Val64Array::value_type x6,
                     BoundLayout<NondetRegLayout64LayoutArray::value_type> x7) {
                  // ThetaP1(zirgen/circuit/keccak2/keccak.zir:13)
                  Val5Array x8 = Val5Array{arg0[0][to_size_t(x3)][to_size_t(x6)],
                                           arg0[1][to_size_t(x3)][to_size_t(x6)],
                                           arg0[2][to_size_t(x3)][to_size_t(x6)],
                                           arg0[3][to_size_t(x3)][to_size_t(x6)],
                                           arg0[4][to_size_t(x3)][to_size_t(x6)]};
                  NondetRegStruct x9 = exec_Xor5(ctx, x8, x7);
                  return ThetaP1_Super_Super_SuperStruct{._super = x9};
                }));
            return ThetaP1_Super_SuperStruct{._super = x5};
          }));
  return ThetaP1Struct{._super = x2};
}
__device__ OneHot_24_Struct exec_OneHot_24_(ExecContext& ctx,
                                            Val arg0,
                                            BoundLayout<OneHot_24_Layout> layout1) {
  // OneHot(zirgen/circuit/keccak2/one_hot.zir:7)
  NondetRegStruct24Array x2 = map(
      Val24Array{Val(0),  Val(1),  Val(2),  Val(3),  Val(4),  Val(5),  Val(6),  Val(7),
                 Val(8),  Val(9),  Val(10), Val(11), Val(12), Val(13), Val(14), Val(15),
                 Val(16), Val(17), Val(18), Val(19), Val(20), Val(21), Val(22), Val(23)},
      LAYOUT_LOOKUP(layout1, _super),
      ([&](Val24Array::value_type x3, BoundLayout<NondetRegLayout24LayoutArray::value_type> x4) {
        NondetRegStruct x5 = exec_NondetBitReg(ctx, isz((x3 - arg0)), x4);
        return x5;
      }));
  // OneHot(zirgen/circuit/keccak2/one_hot.zir:9)
  Val x6 = x2[1]._super;
  Val x7 = (x2[0]._super + x6);
  Val x8 = x2[2]._super;
  Val x9 = x2[3]._super;
  Val x10 = x2[4]._super;
  Val x11 = (((x7 + x8) + x9) + x10);
  Val x12 = x2[5]._super;
  Val x13 = x2[6]._super;
  Val x14 = x2[7]._super;
  Val x15 = (((x11 + x12) + x13) + x14);
  Val x16 = x2[8]._super;
  Val x17 = x2[9]._super;
  Val x18 = x2[10]._super;
  Val x19 = (((x15 + x16) + x17) + x18);
  Val x20 = x2[11]._super;
  Val x21 = x2[12]._super;
  Val x22 = x2[13]._super;
  Val x23 = (((x19 + x20) + x21) + x22);
  Val x24 = x2[14]._super;
  Val x25 = x2[15]._super;
  Val x26 = x2[16]._super;
  Val x27 = (((x23 + x24) + x25) + x26);
  Val x28 = x2[17]._super;
  Val x29 = x2[18]._super;
  Val x30 = x2[19]._super;
  Val x31 = (((x27 + x28) + x29) + x30);
  Val x32 = x2[20]._super;
  Val x33 = x2[21]._super;
  Val x34 = x2[22]._super;
  Val x35 = (((x31 + x32) + x33) + x34);
  Val x36 = x2[23]._super;
  EQZ(((x35 + x36) - Val(1)), "OneHot(zirgen/circuit/keccak2/one_hot.zir:9)");
  // OneHot(zirgen/circuit/keccak2/one_hot.zir:11)
  Val x37 = (((x6 + (x8 * Val(2))) + (x9 * Val(3))) + (x10 * Val(4)));
  Val x38 = (((x37 + (x12 * Val(5))) + (x13 * Val(6))) + (x14 * Val(7)));
  Val x39 = (((x38 + (x16 * Val(8))) + (x17 * Val(9))) + (x18 * Val(10)));
  Val x40 = (((x39 + (x20 * Val(11))) + (x21 * Val(12))) + (x22 * Val(13)));
  Val x41 = (((x40 + (x24 * Val(14))) + (x25 * Val(15))) + (x26 * Val(16)));
  Val x42 = (((x41 + (x28 * Val(17))) + (x29 * Val(18))) + (x30 * Val(19)));
  Val x43 = (((x42 + (x32 * Val(20))) + (x33 * Val(21))) + (x34 * Val(22)));
  EQZ(((x43 + (x36 * Val(23))) - arg0), "OneHot(zirgen/circuit/keccak2/one_hot.zir:11)");
  return OneHot_24_Struct{._super = x2};
}
__device__ CarryExtractStruct exec_CarryExtract(ExecContext& ctx,
                                                Val arg0,
                                                BoundLayout<CarryExtractLayout> layout1) {
  // Div(<preamble>:19)
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:34)
  Val x2 = (bitAnd(arg0, Val(983040)) * Val(2013235201));
  NondetRegStruct x3 = exec_NondetBitReg(ctx, bitAnd(x2, Val(1)), LAYOUT_LOOKUP(layout1, bit0));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:35)
  NondetRegStruct x4 =
      exec_NondetBitReg(ctx, (bitAnd(x2, Val(2)) * Val(1006632961)), LAYOUT_LOOKUP(layout1, bit1));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:36)
  NondetRegStruct x5 =
      exec_NondetBitReg(ctx, (bitAnd(x2, Val(4)) * Val(1509949441)), LAYOUT_LOOKUP(layout1, bit2));
  // CarryExtract(zirgen/circuit/keccak2/sha2.zir:37)
  Val x6 = ((x5._super * Val(4)) + (x4._super * Val(2)));
  Val x7 = (x6 + x3._super);
  return CarryExtractStruct{.carry = x7, .out = (arg0 - (x7 * Val(65536)))};
}
__device__ UnpackReg_32__16_Struct exec_CarryAndExpand(ExecContext& ctx,
                                                       Val2Array arg0,
                                                       BoundLayout<CarryAndExpandLayout> layout1) {
  // CarryAndExpand(zirgen/circuit/keccak2/sha2.zir:42)
  CarryExtractStruct x2 = exec_CarryExtract(ctx, arg0[0], LAYOUT_LOOKUP(layout1, lowCarry));
  // CarryAndExpand(zirgen/circuit/keccak2/sha2.zir:43)
  CarryExtractStruct x3 =
      exec_CarryExtract(ctx, (arg0[1] + x2.carry), LAYOUT_LOOKUP(layout1, highCarry));
  // CarryAndExpand(zirgen/circuit/keccak2/sha2.zir:44)
  UnpackReg_32__16_Struct x4 =
      exec_UnpackReg_32__16_(ctx, Val2Array{x2.out, x3.out}, LAYOUT_LOOKUP(layout1, _super));
  return x4;
}
__device__ TopStateStruct back_TopState(ExecContext& ctx,
                                        Index distance0,
                                        BoundLayout<TopStateLayout> layout1) {
  // TopState(zirgen/circuit/keccak2/top.zir:35)
  TopStateBitsStruct800Array x2 = map(
      Val800Array{
          Val(0),   Val(1),   Val(2),   Val(3),   Val(4),   Val(5),   Val(6),   Val(7),   Val(8),
          Val(9),   Val(10),  Val(11),  Val(12),  Val(13),  Val(14),  Val(15),  Val(16),  Val(17),
          Val(18),  Val(19),  Val(20),  Val(21),  Val(22),  Val(23),  Val(24),  Val(25),  Val(26),
          Val(27),  Val(28),  Val(29),  Val(30),  Val(31),  Val(32),  Val(33),  Val(34),  Val(35),
          Val(36),  Val(37),  Val(38),  Val(39),  Val(40),  Val(41),  Val(42),  Val(43),  Val(44),
          Val(45),  Val(46),  Val(47),  Val(48),  Val(49),  Val(50),  Val(51),  Val(52),  Val(53),
          Val(54),  Val(55),  Val(56),  Val(57),  Val(58),  Val(59),  Val(60),  Val(61),  Val(62),
          Val(63),  Val(64),  Val(65),  Val(66),  Val(67),  Val(68),  Val(69),  Val(70),  Val(71),
          Val(72),  Val(73),  Val(74),  Val(75),  Val(76),  Val(77),  Val(78),  Val(79),  Val(80),
          Val(81),  Val(82),  Val(83),  Val(84),  Val(85),  Val(86),  Val(87),  Val(88),  Val(89),
          Val(90),  Val(91),  Val(92),  Val(93),  Val(94),  Val(95),  Val(96),  Val(97),  Val(98),
          Val(99),  Val(100), Val(101), Val(102), Val(103), Val(104), Val(105), Val(106), Val(107),
          Val(108), Val(109), Val(110), Val(111), Val(112), Val(113), Val(114), Val(115), Val(116),
          Val(117), Val(118), Val(119), Val(120), Val(121), Val(122), Val(123), Val(124), Val(125),
          Val(126), Val(127), Val(128), Val(129), Val(130), Val(131), Val(132), Val(133), Val(134),
          Val(135), Val(136), Val(137), Val(138), Val(139), Val(140), Val(141), Val(142), Val(143),
          Val(144), Val(145), Val(146), Val(147), Val(148), Val(149), Val(150), Val(151), Val(152),
          Val(153), Val(154), Val(155), Val(156), Val(157), Val(158), Val(159), Val(160), Val(161),
          Val(162), Val(163), Val(164), Val(165), Val(166), Val(167), Val(168), Val(169), Val(170),
          Val(171), Val(172), Val(173), Val(174), Val(175), Val(176), Val(177), Val(178), Val(179),
          Val(180), Val(181), Val(182), Val(183), Val(184), Val(185), Val(186), Val(187), Val(188),
          Val(189), Val(190), Val(191), Val(192), Val(193), Val(194), Val(195), Val(196), Val(197),
          Val(198), Val(199), Val(200), Val(201), Val(202), Val(203), Val(204), Val(205), Val(206),
          Val(207), Val(208), Val(209), Val(210), Val(211), Val(212), Val(213), Val(214), Val(215),
          Val(216), Val(217), Val(218), Val(219), Val(220), Val(221), Val(222), Val(223), Val(224),
          Val(225), Val(226), Val(227), Val(228), Val(229), Val(230), Val(231), Val(232), Val(233),
          Val(234), Val(235), Val(236), Val(237), Val(238), Val(239), Val(240), Val(241), Val(242),
          Val(243), Val(244), Val(245), Val(246), Val(247), Val(248), Val(249), Val(250), Val(251),
          Val(252), Val(253), Val(254), Val(255), Val(256), Val(257), Val(258), Val(259), Val(260),
          Val(261), Val(262), Val(263), Val(264), Val(265), Val(266), Val(267), Val(268), Val(269),
          Val(270), Val(271), Val(272), Val(273), Val(274), Val(275), Val(276), Val(277), Val(278),
          Val(279), Val(280), Val(281), Val(282), Val(283), Val(284), Val(285), Val(286), Val(287),
          Val(288), Val(289), Val(290), Val(291), Val(292), Val(293), Val(294), Val(295), Val(296),
          Val(297), Val(298), Val(299), Val(300), Val(301), Val(302), Val(303), Val(304), Val(305),
          Val(306), Val(307), Val(308), Val(309), Val(310), Val(311), Val(312), Val(313), Val(314),
          Val(315), Val(316), Val(317), Val(318), Val(319), Val(320), Val(321), Val(322), Val(323),
          Val(324), Val(325), Val(326), Val(327), Val(328), Val(329), Val(330), Val(331), Val(332),
          Val(333), Val(334), Val(335), Val(336), Val(337), Val(338), Val(339), Val(340), Val(341),
          Val(342), Val(343), Val(344), Val(345), Val(346), Val(347), Val(348), Val(349), Val(350),
          Val(351), Val(352), Val(353), Val(354), Val(355), Val(356), Val(357), Val(358), Val(359),
          Val(360), Val(361), Val(362), Val(363), Val(364), Val(365), Val(366), Val(367), Val(368),
          Val(369), Val(370), Val(371), Val(372), Val(373), Val(374), Val(375), Val(376), Val(377),
          Val(378), Val(379), Val(380), Val(381), Val(382), Val(383), Val(384), Val(385), Val(386),
          Val(387), Val(388), Val(389), Val(390), Val(391), Val(392), Val(393), Val(394), Val(395),
          Val(396), Val(397), Val(398), Val(399), Val(400), Val(401), Val(402), Val(403), Val(404),
          Val(405), Val(406), Val(407), Val(408), Val(409), Val(410), Val(411), Val(412), Val(413),
          Val(414), Val(415), Val(416), Val(417), Val(418), Val(419), Val(420), Val(421), Val(422),
          Val(423), Val(424), Val(425), Val(426), Val(427), Val(428), Val(429), Val(430), Val(431),
          Val(432), Val(433), Val(434), Val(435), Val(436), Val(437), Val(438), Val(439), Val(440),
          Val(441), Val(442), Val(443), Val(444), Val(445), Val(446), Val(447), Val(448), Val(449),
          Val(450), Val(451), Val(452), Val(453), Val(454), Val(455), Val(456), Val(457), Val(458),
          Val(459), Val(460), Val(461), Val(462), Val(463), Val(464), Val(465), Val(466), Val(467),
          Val(468), Val(469), Val(470), Val(471), Val(472), Val(473), Val(474), Val(475), Val(476),
          Val(477), Val(478), Val(479), Val(480), Val(481), Val(482), Val(483), Val(484), Val(485),
          Val(486), Val(487), Val(488), Val(489), Val(490), Val(491), Val(492), Val(493), Val(494),
          Val(495), Val(496), Val(497), Val(498), Val(499), Val(500), Val(501), Val(502), Val(503),
          Val(504), Val(505), Val(506), Val(507), Val(508), Val(509), Val(510), Val(511), Val(512),
          Val(513), Val(514), Val(515), Val(516), Val(517), Val(518), Val(519), Val(520), Val(521),
          Val(522), Val(523), Val(524), Val(525), Val(526), Val(527), Val(528), Val(529), Val(530),
          Val(531), Val(532), Val(533), Val(534), Val(535), Val(536), Val(537), Val(538), Val(539),
          Val(540), Val(541), Val(542), Val(543), Val(544), Val(545), Val(546), Val(547), Val(548),
          Val(549), Val(550), Val(551), Val(552), Val(553), Val(554), Val(555), Val(556), Val(557),
          Val(558), Val(559), Val(560), Val(561), Val(562), Val(563), Val(564), Val(565), Val(566),
          Val(567), Val(568), Val(569), Val(570), Val(571), Val(572), Val(573), Val(574), Val(575),
          Val(576), Val(577), Val(578), Val(579), Val(580), Val(581), Val(582), Val(583), Val(584),
          Val(585), Val(586), Val(587), Val(588), Val(589), Val(590), Val(591), Val(592), Val(593),
          Val(594), Val(595), Val(596), Val(597), Val(598), Val(599), Val(600), Val(601), Val(602),
          Val(603), Val(604), Val(605), Val(606), Val(607), Val(608), Val(609), Val(610), Val(611),
          Val(612), Val(613), Val(614), Val(615), Val(616), Val(617), Val(618), Val(619), Val(620),
          Val(621), Val(622), Val(623), Val(624), Val(625), Val(626), Val(627), Val(628), Val(629),
          Val(630), Val(631), Val(632), Val(633), Val(634), Val(635), Val(636), Val(637), Val(638),
          Val(639), Val(640), Val(641), Val(642), Val(643), Val(644), Val(645), Val(646), Val(647),
          Val(648), Val(649), Val(650), Val(651), Val(652), Val(653), Val(654), Val(655), Val(656),
          Val(657), Val(658), Val(659), Val(660), Val(661), Val(662), Val(663), Val(664), Val(665),
          Val(666), Val(667), Val(668), Val(669), Val(670), Val(671), Val(672), Val(673), Val(674),
          Val(675), Val(676), Val(677), Val(678), Val(679), Val(680), Val(681), Val(682), Val(683),
          Val(684), Val(685), Val(686), Val(687), Val(688), Val(689), Val(690), Val(691), Val(692),
          Val(693), Val(694), Val(695), Val(696), Val(697), Val(698), Val(699), Val(700), Val(701),
          Val(702), Val(703), Val(704), Val(705), Val(706), Val(707), Val(708), Val(709), Val(710),
          Val(711), Val(712), Val(713), Val(714), Val(715), Val(716), Val(717), Val(718), Val(719),
          Val(720), Val(721), Val(722), Val(723), Val(724), Val(725), Val(726), Val(727), Val(728),
          Val(729), Val(730), Val(731), Val(732), Val(733), Val(734), Val(735), Val(736), Val(737),
          Val(738), Val(739), Val(740), Val(741), Val(742), Val(743), Val(744), Val(745), Val(746),
          Val(747), Val(748), Val(749), Val(750), Val(751), Val(752), Val(753), Val(754), Val(755),
          Val(756), Val(757), Val(758), Val(759), Val(760), Val(761), Val(762), Val(763), Val(764),
          Val(765), Val(766), Val(767), Val(768), Val(769), Val(770), Val(771), Val(772), Val(773),
          Val(774), Val(775), Val(776), Val(777), Val(778), Val(779), Val(780), Val(781), Val(782),
          Val(783), Val(784), Val(785), Val(786), Val(787), Val(788), Val(789), Val(790), Val(791),
          Val(792), Val(793), Val(794), Val(795), Val(796), Val(797), Val(798), Val(799)},
      LAYOUT_LOOKUP(layout1, bits),
      ([&](Val800Array::value_type x3, BoundLayout<NondetRegLayout800LayoutArray::value_type> x4) {
        // TopState(zirgen/circuit/keccak2/top.zir:36)
        NondetRegStruct x5 = back_Reg(ctx, distance0, x4);
        return TopStateBitsStruct{._super = x5};
      }));
  // TopState(zirgen/circuit/keccak2/top.zir:39)
  TopStateKflatStruct100Array x6 = map(
      Val100Array{
          Val(0),  Val(1),  Val(2),  Val(3),  Val(4),  Val(5),  Val(6),  Val(7),  Val(8),  Val(9),
          Val(10), Val(11), Val(12), Val(13), Val(14), Val(15), Val(16), Val(17), Val(18), Val(19),
          Val(20), Val(21), Val(22), Val(23), Val(24), Val(25), Val(26), Val(27), Val(28), Val(29),
          Val(30), Val(31), Val(32), Val(33), Val(34), Val(35), Val(36), Val(37), Val(38), Val(39),
          Val(40), Val(41), Val(42), Val(43), Val(44), Val(45), Val(46), Val(47), Val(48), Val(49),
          Val(50), Val(51), Val(52), Val(53), Val(54), Val(55), Val(56), Val(57), Val(58), Val(59),
          Val(60), Val(61), Val(62), Val(63), Val(64), Val(65), Val(66), Val(67), Val(68), Val(69),
          Val(70), Val(71), Val(72), Val(73), Val(74), Val(75), Val(76), Val(77), Val(78), Val(79),
          Val(80), Val(81), Val(82), Val(83), Val(84), Val(85), Val(86), Val(87), Val(88), Val(89),
          Val(90), Val(91), Val(92), Val(93), Val(94), Val(95), Val(96), Val(97), Val(98), Val(99)},
      LAYOUT_LOOKUP(layout1, kflat),
      ([&](Val100Array::value_type x7, BoundLayout<NondetRegLayout100LayoutArray::value_type> x8) {
        // TopState(zirgen/circuit/keccak2/top.zir:40)
        NondetRegStruct x9 = back_Reg(ctx, distance0, x8);
        return TopStateKflatStruct{._super = x9};
      }));
  // TopState(zirgen/circuit/keccak2/top.zir:42)
  NondetRegStruct16Array x10 = map(
      Val16Array{Val(0),
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
                 Val(11),
                 Val(12),
                 Val(13),
                 Val(14),
                 Val(15)},
      LAYOUT_LOOKUP(layout1, sflat),
      ([&](Val16Array::value_type x11, BoundLayout<NondetRegLayout16LayoutArray::value_type> x12) {
        // TopState(zirgen/circuit/keccak2/top.zir:43)
        NondetRegStruct x13 = back_Reg(ctx, distance0, x12);
        return x13;
      }));
  return TopStateStruct{.bits = x2, .kflat = x6, .sflat = x10};
}
__device__ TopStateStruct exec_TopState(ExecContext& ctx,
                                        Val800Array arg0,
                                        Val100Array arg1,
                                        Val16Array arg2,
                                        BoundLayout<TopStateLayout> layout3) {
  // TopState(zirgen/circuit/keccak2/top.zir:35)
  TopStateBitsStruct800Array x4 = map(
      Val800Array{
          Val(0),   Val(1),   Val(2),   Val(3),   Val(4),   Val(5),   Val(6),   Val(7),   Val(8),
          Val(9),   Val(10),  Val(11),  Val(12),  Val(13),  Val(14),  Val(15),  Val(16),  Val(17),
          Val(18),  Val(19),  Val(20),  Val(21),  Val(22),  Val(23),  Val(24),  Val(25),  Val(26),
          Val(27),  Val(28),  Val(29),  Val(30),  Val(31),  Val(32),  Val(33),  Val(34),  Val(35),
          Val(36),  Val(37),  Val(38),  Val(39),  Val(40),  Val(41),  Val(42),  Val(43),  Val(44),
          Val(45),  Val(46),  Val(47),  Val(48),  Val(49),  Val(50),  Val(51),  Val(52),  Val(53),
          Val(54),  Val(55),  Val(56),  Val(57),  Val(58),  Val(59),  Val(60),  Val(61),  Val(62),
          Val(63),  Val(64),  Val(65),  Val(66),  Val(67),  Val(68),  Val(69),  Val(70),  Val(71),
          Val(72),  Val(73),  Val(74),  Val(75),  Val(76),  Val(77),  Val(78),  Val(79),  Val(80),
          Val(81),  Val(82),  Val(83),  Val(84),  Val(85),  Val(86),  Val(87),  Val(88),  Val(89),
          Val(90),  Val(91),  Val(92),  Val(93),  Val(94),  Val(95),  Val(96),  Val(97),  Val(98),
          Val(99),  Val(100), Val(101), Val(102), Val(103), Val(104), Val(105), Val(106), Val(107),
          Val(108), Val(109), Val(110), Val(111), Val(112), Val(113), Val(114), Val(115), Val(116),
          Val(117), Val(118), Val(119), Val(120), Val(121), Val(122), Val(123), Val(124), Val(125),
          Val(126), Val(127), Val(128), Val(129), Val(130), Val(131), Val(132), Val(133), Val(134),
          Val(135), Val(136), Val(137), Val(138), Val(139), Val(140), Val(141), Val(142), Val(143),
          Val(144), Val(145), Val(146), Val(147), Val(148), Val(149), Val(150), Val(151), Val(152),
          Val(153), Val(154), Val(155), Val(156), Val(157), Val(158), Val(159), Val(160), Val(161),
          Val(162), Val(163), Val(164), Val(165), Val(166), Val(167), Val(168), Val(169), Val(170),
          Val(171), Val(172), Val(173), Val(174), Val(175), Val(176), Val(177), Val(178), Val(179),
          Val(180), Val(181), Val(182), Val(183), Val(184), Val(185), Val(186), Val(187), Val(188),
          Val(189), Val(190), Val(191), Val(192), Val(193), Val(194), Val(195), Val(196), Val(197),
          Val(198), Val(199), Val(200), Val(201), Val(202), Val(203), Val(204), Val(205), Val(206),
          Val(207), Val(208), Val(209), Val(210), Val(211), Val(212), Val(213), Val(214), Val(215),
          Val(216), Val(217), Val(218), Val(219), Val(220), Val(221), Val(222), Val(223), Val(224),
          Val(225), Val(226), Val(227), Val(228), Val(229), Val(230), Val(231), Val(232), Val(233),
          Val(234), Val(235), Val(236), Val(237), Val(238), Val(239), Val(240), Val(241), Val(242),
          Val(243), Val(244), Val(245), Val(246), Val(247), Val(248), Val(249), Val(250), Val(251),
          Val(252), Val(253), Val(254), Val(255), Val(256), Val(257), Val(258), Val(259), Val(260),
          Val(261), Val(262), Val(263), Val(264), Val(265), Val(266), Val(267), Val(268), Val(269),
          Val(270), Val(271), Val(272), Val(273), Val(274), Val(275), Val(276), Val(277), Val(278),
          Val(279), Val(280), Val(281), Val(282), Val(283), Val(284), Val(285), Val(286), Val(287),
          Val(288), Val(289), Val(290), Val(291), Val(292), Val(293), Val(294), Val(295), Val(296),
          Val(297), Val(298), Val(299), Val(300), Val(301), Val(302), Val(303), Val(304), Val(305),
          Val(306), Val(307), Val(308), Val(309), Val(310), Val(311), Val(312), Val(313), Val(314),
          Val(315), Val(316), Val(317), Val(318), Val(319), Val(320), Val(321), Val(322), Val(323),
          Val(324), Val(325), Val(326), Val(327), Val(328), Val(329), Val(330), Val(331), Val(332),
          Val(333), Val(334), Val(335), Val(336), Val(337), Val(338), Val(339), Val(340), Val(341),
          Val(342), Val(343), Val(344), Val(345), Val(346), Val(347), Val(348), Val(349), Val(350),
          Val(351), Val(352), Val(353), Val(354), Val(355), Val(356), Val(357), Val(358), Val(359),
          Val(360), Val(361), Val(362), Val(363), Val(364), Val(365), Val(366), Val(367), Val(368),
          Val(369), Val(370), Val(371), Val(372), Val(373), Val(374), Val(375), Val(376), Val(377),
          Val(378), Val(379), Val(380), Val(381), Val(382), Val(383), Val(384), Val(385), Val(386),
          Val(387), Val(388), Val(389), Val(390), Val(391), Val(392), Val(393), Val(394), Val(395),
          Val(396), Val(397), Val(398), Val(399), Val(400), Val(401), Val(402), Val(403), Val(404),
          Val(405), Val(406), Val(407), Val(408), Val(409), Val(410), Val(411), Val(412), Val(413),
          Val(414), Val(415), Val(416), Val(417), Val(418), Val(419), Val(420), Val(421), Val(422),
          Val(423), Val(424), Val(425), Val(426), Val(427), Val(428), Val(429), Val(430), Val(431),
          Val(432), Val(433), Val(434), Val(435), Val(436), Val(437), Val(438), Val(439), Val(440),
          Val(441), Val(442), Val(443), Val(444), Val(445), Val(446), Val(447), Val(448), Val(449),
          Val(450), Val(451), Val(452), Val(453), Val(454), Val(455), Val(456), Val(457), Val(458),
          Val(459), Val(460), Val(461), Val(462), Val(463), Val(464), Val(465), Val(466), Val(467),
          Val(468), Val(469), Val(470), Val(471), Val(472), Val(473), Val(474), Val(475), Val(476),
          Val(477), Val(478), Val(479), Val(480), Val(481), Val(482), Val(483), Val(484), Val(485),
          Val(486), Val(487), Val(488), Val(489), Val(490), Val(491), Val(492), Val(493), Val(494),
          Val(495), Val(496), Val(497), Val(498), Val(499), Val(500), Val(501), Val(502), Val(503),
          Val(504), Val(505), Val(506), Val(507), Val(508), Val(509), Val(510), Val(511), Val(512),
          Val(513), Val(514), Val(515), Val(516), Val(517), Val(518), Val(519), Val(520), Val(521),
          Val(522), Val(523), Val(524), Val(525), Val(526), Val(527), Val(528), Val(529), Val(530),
          Val(531), Val(532), Val(533), Val(534), Val(535), Val(536), Val(537), Val(538), Val(539),
          Val(540), Val(541), Val(542), Val(543), Val(544), Val(545), Val(546), Val(547), Val(548),
          Val(549), Val(550), Val(551), Val(552), Val(553), Val(554), Val(555), Val(556), Val(557),
          Val(558), Val(559), Val(560), Val(561), Val(562), Val(563), Val(564), Val(565), Val(566),
          Val(567), Val(568), Val(569), Val(570), Val(571), Val(572), Val(573), Val(574), Val(575),
          Val(576), Val(577), Val(578), Val(579), Val(580), Val(581), Val(582), Val(583), Val(584),
          Val(585), Val(586), Val(587), Val(588), Val(589), Val(590), Val(591), Val(592), Val(593),
          Val(594), Val(595), Val(596), Val(597), Val(598), Val(599), Val(600), Val(601), Val(602),
          Val(603), Val(604), Val(605), Val(606), Val(607), Val(608), Val(609), Val(610), Val(611),
          Val(612), Val(613), Val(614), Val(615), Val(616), Val(617), Val(618), Val(619), Val(620),
          Val(621), Val(622), Val(623), Val(624), Val(625), Val(626), Val(627), Val(628), Val(629),
          Val(630), Val(631), Val(632), Val(633), Val(634), Val(635), Val(636), Val(637), Val(638),
          Val(639), Val(640), Val(641), Val(642), Val(643), Val(644), Val(645), Val(646), Val(647),
          Val(648), Val(649), Val(650), Val(651), Val(652), Val(653), Val(654), Val(655), Val(656),
          Val(657), Val(658), Val(659), Val(660), Val(661), Val(662), Val(663), Val(664), Val(665),
          Val(666), Val(667), Val(668), Val(669), Val(670), Val(671), Val(672), Val(673), Val(674),
          Val(675), Val(676), Val(677), Val(678), Val(679), Val(680), Val(681), Val(682), Val(683),
          Val(684), Val(685), Val(686), Val(687), Val(688), Val(689), Val(690), Val(691), Val(692),
          Val(693), Val(694), Val(695), Val(696), Val(697), Val(698), Val(699), Val(700), Val(701),
          Val(702), Val(703), Val(704), Val(705), Val(706), Val(707), Val(708), Val(709), Val(710),
          Val(711), Val(712), Val(713), Val(714), Val(715), Val(716), Val(717), Val(718), Val(719),
          Val(720), Val(721), Val(722), Val(723), Val(724), Val(725), Val(726), Val(727), Val(728),
          Val(729), Val(730), Val(731), Val(732), Val(733), Val(734), Val(735), Val(736), Val(737),
          Val(738), Val(739), Val(740), Val(741), Val(742), Val(743), Val(744), Val(745), Val(746),
          Val(747), Val(748), Val(749), Val(750), Val(751), Val(752), Val(753), Val(754), Val(755),
          Val(756), Val(757), Val(758), Val(759), Val(760), Val(761), Val(762), Val(763), Val(764),
          Val(765), Val(766), Val(767), Val(768), Val(769), Val(770), Val(771), Val(772), Val(773),
          Val(774), Val(775), Val(776), Val(777), Val(778), Val(779), Val(780), Val(781), Val(782),
          Val(783), Val(784), Val(785), Val(786), Val(787), Val(788), Val(789), Val(790), Val(791),
          Val(792), Val(793), Val(794), Val(795), Val(796), Val(797), Val(798), Val(799)},
      LAYOUT_LOOKUP(layout3, bits),
      ([&](Val800Array::value_type x5, BoundLayout<NondetRegLayout800LayoutArray::value_type> x6) {
        // TopState(zirgen/circuit/keccak2/top.zir:36)
        NondetRegStruct x7 = exec_Reg(ctx, arg0[to_size_t(x5)], x6);
        return TopStateBitsStruct{._super = x7};
      }));
  // TopState(zirgen/circuit/keccak2/top.zir:39)
  TopStateKflatStruct100Array x8 = map(
      Val100Array{
          Val(0),  Val(1),  Val(2),  Val(3),  Val(4),  Val(5),  Val(6),  Val(7),  Val(8),  Val(9),
          Val(10), Val(11), Val(12), Val(13), Val(14), Val(15), Val(16), Val(17), Val(18), Val(19),
          Val(20), Val(21), Val(22), Val(23), Val(24), Val(25), Val(26), Val(27), Val(28), Val(29),
          Val(30), Val(31), Val(32), Val(33), Val(34), Val(35), Val(36), Val(37), Val(38), Val(39),
          Val(40), Val(41), Val(42), Val(43), Val(44), Val(45), Val(46), Val(47), Val(48), Val(49),
          Val(50), Val(51), Val(52), Val(53), Val(54), Val(55), Val(56), Val(57), Val(58), Val(59),
          Val(60), Val(61), Val(62), Val(63), Val(64), Val(65), Val(66), Val(67), Val(68), Val(69),
          Val(70), Val(71), Val(72), Val(73), Val(74), Val(75), Val(76), Val(77), Val(78), Val(79),
          Val(80), Val(81), Val(82), Val(83), Val(84), Val(85), Val(86), Val(87), Val(88), Val(89),
          Val(90), Val(91), Val(92), Val(93), Val(94), Val(95), Val(96), Val(97), Val(98), Val(99)},
      LAYOUT_LOOKUP(layout3, kflat),
      ([&](Val100Array::value_type x9, BoundLayout<NondetRegLayout100LayoutArray::value_type> x10) {
        // TopState(zirgen/circuit/keccak2/top.zir:40)
        NondetRegStruct x11 = exec_Reg(ctx, arg1[to_size_t(x9)], x10);
        return TopStateKflatStruct{._super = x11};
      }));
  // TopState(zirgen/circuit/keccak2/top.zir:42)
  NondetRegStruct16Array x12 = map(
      Val16Array{Val(0),
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
                 Val(11),
                 Val(12),
                 Val(13),
                 Val(14),
                 Val(15)},
      LAYOUT_LOOKUP(layout3, sflat),
      ([&](Val16Array::value_type x13, BoundLayout<NondetRegLayout16LayoutArray::value_type> x14) {
        // TopState(zirgen/circuit/keccak2/top.zir:43)
        NondetRegStruct x15 = exec_Reg(ctx, arg2[to_size_t(x13)], x14);
        return x15;
      }));
  return TopStateStruct{.bits = x4, .kflat = x8, .sflat = x12};
}
__device__ OneHot_8_Struct exec_OneHot_8_(ExecContext& ctx,
                                          Val arg0,
                                          BoundLayout<OneHot_8_Layout> layout1) {
  // OneHot(zirgen/circuit/keccak2/one_hot.zir:7)
  NondetRegStruct8Array x2 =
      map(Val8Array{Val(0), Val(1), Val(2), Val(3), Val(4), Val(5), Val(6), Val(7)},
          LAYOUT_LOOKUP(layout1, _super),
          ([&](Val8Array::value_type x3, BoundLayout<NondetRegLayout8LayoutArray::value_type> x4) {
            NondetRegStruct x5 = exec_NondetBitReg(ctx, isz((x3 - arg0)), x4);
            return x5;
          }));
  // OneHot(zirgen/circuit/keccak2/one_hot.zir:9)
  Val x6 = x2[1]._super;
  Val x7 = (x2[0]._super + x6);
  Val x8 = x2[2]._super;
  Val x9 = x2[3]._super;
  Val x10 = x2[4]._super;
  Val x11 = (((x7 + x8) + x9) + x10);
  Val x12 = x2[5]._super;
  Val x13 = x2[6]._super;
  Val x14 = x2[7]._super;
  Val x15 = (((x11 + x12) + x13) + x14);
  EQZ((x15 - Val(1)), "OneHot(zirgen/circuit/keccak2/one_hot.zir:9)");
  // OneHot(zirgen/circuit/keccak2/one_hot.zir:11)
  Val x16 = (((x6 + (x8 * Val(2))) + (x9 * Val(3))) + (x10 * Val(4)));
  Val x17 = (((x16 + (x12 * Val(5))) + (x13 * Val(6))) + (x14 * Val(7)));
  EQZ((x17 - arg0), "OneHot(zirgen/circuit/keccak2/one_hot.zir:11)");
  return OneHot_8_Struct{._super = x2};
}
__device__ OneHot_4_Struct exec_OneHot_4_(ExecContext& ctx,
                                          Val arg0,
                                          BoundLayout<OneHot_4_Layout> layout1) {
  // OneHot(zirgen/circuit/keccak2/one_hot.zir:7)
  NondetRegStruct4Array x2 =
      map(Val4Array{Val(0), Val(1), Val(2), Val(3)},
          LAYOUT_LOOKUP(layout1, _super),
          ([&](Val4Array::value_type x3, BoundLayout<NondetRegLayout4LayoutArray::value_type> x4) {
            NondetRegStruct x5 = exec_NondetBitReg(ctx, isz((x3 - arg0)), x4);
            return x5;
          }));
  // OneHot(zirgen/circuit/keccak2/one_hot.zir:9)
  Val x6 = x2[1]._super;
  Val x7 = (x2[0]._super + x6);
  Val x8 = x2[2]._super;
  Val x9 = x2[3]._super;
  Val x10 = (((x7 + x8) + x9) - Val(1));
  EQZ(x10, "OneHot(zirgen/circuit/keccak2/one_hot.zir:9)");
  // OneHot(zirgen/circuit/keccak2/one_hot.zir:11)
  Val x11 = (((x6 + (x8 * Val(2))) + (x9 * Val(3))) - arg0);
  EQZ(x11, "OneHot(zirgen/circuit/keccak2/one_hot.zir:11)");
  return OneHot_4_Struct{._super = x2};
}
__device__ LoadWinStruct exec_LoadWin(ExecContext& ctx,
                                      Val100Array arg0,
                                      OneHot_8_Struct arg1,
                                      Val arg2,
                                      BoundLayout<LoadWinLayout> layout3) {
  // LoadWin(zirgen/circuit/keccak2/top.zir:166)
  OneHot_4_Struct x4 = exec_OneHot_4_(ctx, arg2, LAYOUT_LOOKUP(layout3, blockSelect));
  // LoadWin(zirgen/circuit/keccak2/top.zir:165)
  NondetRegStruct8Array x5 = arg1._super;
  // LoadWin(zirgen/circuit/keccak2/top.zir:167)
  Val x6 = (x5[2]._super + x5[3]._super);
  Val x7 = ((x6 + x5[4]._super) + x5[5]._super);
  Val x8 = ((x7 + x5[6]._super) + x5[7]._super);
  // LoadWin(zirgen/circuit/keccak2/top.zir:166)
  NondetRegStruct4Array x9 = x4._super;
  // LoadWin(zirgen/circuit/keccak2/top.zir:173)
  Val2Array x10 = Val2Array{Val(0), Val(0)};
  // LoadWin(zirgen/circuit/keccak2/top.zir:176)
  Val2Array8Array x11 = Val2Array8Array{x10, x10, x10, x10, x10, x10, x10, x10};
  Val2Array8Array x12;
  if (to_size_t(x5[0]._super)) {
    Val2Array8Array x13;
    if (to_size_t(x9[0]._super)) {
      // LoadWin(zirgen/circuit/keccak2/top.zir:169)
      Val2Array8Array x14 = Val2Array8Array{Val2Array{arg0[0], arg0[1]},
                                            Val2Array{arg0[2], arg0[3]},
                                            Val2Array{arg0[4], arg0[5]},
                                            Val2Array{arg0[6], arg0[7]},
                                            Val2Array{arg0[8], arg0[9]},
                                            Val2Array{arg0[10], arg0[11]},
                                            Val2Array{arg0[12], arg0[13]},
                                            Val2Array{arg0[14], arg0[15]}};
      x13 = x14;
    } else if (to_size_t(x9[1]._super)) {
      Val2Array8Array x15 = Val2Array8Array{Val2Array{arg0[32], arg0[33]},
                                            Val2Array{arg0[34], arg0[35]},
                                            Val2Array{arg0[36], arg0[37]},
                                            Val2Array{arg0[38], arg0[39]},
                                            Val2Array{arg0[40], arg0[41]},
                                            Val2Array{arg0[42], arg0[43]},
                                            Val2Array{arg0[44], arg0[45]},
                                            Val2Array{arg0[46], arg0[47]}};
      x13 = x15;
    } else if (to_size_t(x9[2]._super)) {
      Val2Array8Array x16 = Val2Array8Array{Val2Array{arg0[64], arg0[65]},
                                            Val2Array{arg0[66], arg0[67]},
                                            Val2Array{arg0[68], arg0[69]},
                                            Val2Array{arg0[70], arg0[71]},
                                            Val2Array{arg0[72], arg0[73]},
                                            Val2Array{arg0[74], arg0[75]},
                                            Val2Array{arg0[76], arg0[77]},
                                            Val2Array{arg0[78], arg0[79]}};
      x13 = x16;
    } else if (to_size_t(x9[3]._super)) {
      // LoadWin(zirgen/circuit/keccak2/top.zir:173)
      Val2Array8Array x17 = Val2Array8Array{Val2Array{arg0[96], arg0[97]},
                                            Val2Array{arg0[98], arg0[99]},
                                            x10,
                                            x10,
                                            x10,
                                            x10,
                                            x10,
                                            x10};
      x13 = x17;
    } else {
      assert(0 && "Reached unreachable mux arm");
    }
    x12 = x13;
  } else if (to_size_t(x5[1]._super)) {
    Val2Array8Array x18;
    if (to_size_t(x9[0]._super)) {
      // LoadWin(zirgen/circuit/keccak2/top.zir:176)
      Val2Array8Array x19 = Val2Array8Array{Val2Array{arg0[16], arg0[17]},
                                            Val2Array{arg0[18], arg0[19]},
                                            Val2Array{arg0[20], arg0[21]},
                                            Val2Array{arg0[22], arg0[23]},
                                            Val2Array{arg0[24], arg0[25]},
                                            Val2Array{arg0[26], arg0[27]},
                                            Val2Array{arg0[28], arg0[29]},
                                            Val2Array{arg0[30], arg0[31]}};
      x18 = x19;
    } else if (to_size_t(x9[1]._super)) {
      Val2Array8Array x20 = Val2Array8Array{Val2Array{arg0[48], arg0[49]},
                                            Val2Array{arg0[50], arg0[51]},
                                            Val2Array{arg0[52], arg0[53]},
                                            Val2Array{arg0[54], arg0[55]},
                                            Val2Array{arg0[56], arg0[57]},
                                            Val2Array{arg0[58], arg0[59]},
                                            Val2Array{arg0[60], arg0[61]},
                                            Val2Array{arg0[62], arg0[63]}};
      x18 = x20;
    } else if (to_size_t(x9[2]._super)) {
      Val2Array8Array x21 = Val2Array8Array{Val2Array{arg0[80], arg0[81]},
                                            Val2Array{arg0[82], arg0[83]},
                                            Val2Array{arg0[84], arg0[85]},
                                            Val2Array{arg0[86], arg0[87]},
                                            Val2Array{arg0[88], arg0[89]},
                                            Val2Array{arg0[90], arg0[91]},
                                            Val2Array{arg0[92], arg0[93]},
                                            Val2Array{arg0[94], arg0[95]}};
      x18 = x21;
    } else if (to_size_t(x9[3]._super)) {
      x18 = x11;
    } else {
      assert(0 && "Reached unreachable mux arm");
    }
    x12 = x18;
  } else if (to_size_t(x8)) {
    x12 = x11;
  } else {
    assert(0 && "Reached unreachable mux arm");
  }
  return LoadWinStruct{._super = x12};
}
__device__ TopStateStruct exec_InitCycle(ExecContext& ctx, BoundLayout<TopStateLayout> layout0) {
  // Log(<preamble>:22)
  // InitCycle(zirgen/circuit/keccak2/top.zir:307)
  INVOKE_EXTERN(ctx, log, "InitCycle", std::initializer_list<Val>{});
  // InitCycle(zirgen/circuit/keccak2/top.zir:316)
  TopStateStruct x1 = exec_TopState(
      ctx,
      Val800Array{
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
          Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0)},
      Val100Array{Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
                  Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
                  Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
                  Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
                  Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
                  Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
                  Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
                  Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
                  Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0),
                  Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0), Val(0)},
      Val16Array{Val(58983),
                 Val(27145),
                 Val(44677),
                 Val(47975),
                 Val(62322),
                 Val(15470),
                 Val(62778),
                 Val(42319),
                 Val(21119),
                 Val(20750),
                 Val(26764),
                 Val(39685),
                 Val(55723),
                 Val(8067),
                 Val(52505),
                 Val(23520)},
      layout0);
  return x1;
}
__device__ UnpackReg_800__16_Struct
exec_SFlatToBits(ExecContext& ctx, Val16Array arg0, BoundLayout<UnpackReg_800__16_Layout> layout1) {
  // SFlatToBits(zirgen/circuit/keccak2/top.zir:329)
  UnpackReg_800__16_Struct x2 = exec_UnpackReg_800__16_(
      ctx,
      Val50Array{Val(0),   Val(0),   Val(0),   Val(0),   Val(0),   Val(0),   Val(0),  Val(0),
                 arg0[6],  arg0[7],  arg0[4],  arg0[5],  arg0[2],  arg0[3],  arg0[0], arg0[1],
                 Val(0),   Val(0),   Val(0),   Val(0),   Val(0),   Val(0),   Val(0),  Val(0),
                 arg0[14], arg0[15], arg0[12], arg0[13], arg0[10], arg0[11], arg0[8], arg0[9],
                 Val(0),   Val(0),   Val(0),   Val(0),   Val(0),   Val(0),   Val(0),  Val(0),
                 Val(0),   Val(0),   Val(0),   Val(0),   Val(0),   Val(0),   Val(0),  Val(0),
                 Val(0),   Val(0)},
      layout1);
  return x2;
}
__device__ DigestRegStruct exec_DigestReg(ExecContext& ctx,
                                          Val16Array arg0,
                                          BoundLayout<DigestRegLayout> layout1) {
  // DigestReg(zirgen/circuit/keccak2/top.zir:391)
  DigestRegValuesStruct16Array x2 = map(
      arg0,
      LAYOUT_LOOKUP(layout1, values),
      ([&](Val16Array::value_type x3, BoundLayout<NondetRegLayout16LayoutArray::value_type> x4) {
        NondetRegStruct x5 = exec_Reg(ctx, x3, x4);
        return DigestRegValuesStruct{};
      }));
  return DigestRegStruct{};
}
__device__ ControlStateStruct back_ControlState(ExecContext& ctx,
                                                Index distance0,
                                                BoundLayout<ControlStateLayout> layout1) {
  // ControlState(zirgen/circuit/keccak2/top.zir:403)
  NondetRegStruct x2 = back_Reg(ctx, distance0, LAYOUT_LOOKUP(layout1, cycleType));
  // ControlState(zirgen/circuit/keccak2/top.zir:404)
  NondetRegStruct x3 = back_Reg(ctx, distance0, LAYOUT_LOOKUP(layout1, subType));
  // ControlState(zirgen/circuit/keccak2/top.zir:405)
  NondetRegStruct x4 = back_Reg(ctx, distance0, LAYOUT_LOOKUP(layout1, block));
  // ControlState(zirgen/circuit/keccak2/top.zir:406)
  NondetRegStruct x5 = back_Reg(ctx, distance0, LAYOUT_LOOKUP(layout1, round));
  return ControlStateStruct{.cycleType = x2, .subType = x3, .block = x4, .round = x5};
}
__device__ ControlStateStruct exec_ControlState(ExecContext& ctx,
                                                Val arg0,
                                                Val arg1,
                                                Val arg2,
                                                Val arg3,
                                                BoundLayout<ControlStateLayout> layout4) {
  // ControlState(zirgen/circuit/keccak2/top.zir:403)
  NondetRegStruct x5 = exec_Reg(ctx, arg0, LAYOUT_LOOKUP(layout4, cycleType));
  // ControlState(zirgen/circuit/keccak2/top.zir:404)
  NondetRegStruct x6 = exec_Reg(ctx, arg1, LAYOUT_LOOKUP(layout4, subType));
  // ControlState(zirgen/circuit/keccak2/top.zir:405)
  NondetRegStruct x7 = exec_Reg(ctx, arg2, LAYOUT_LOOKUP(layout4, block));
  // ControlState(zirgen/circuit/keccak2/top.zir:406)
  NondetRegStruct x8 = exec_Reg(ctx, arg3, LAYOUT_LOOKUP(layout4, round));
  return ControlStateStruct{.cycleType = x5, .subType = x6, .block = x7, .round = x8};
}
__device__ ControlStateStruct exec_KeccackNextRound(ExecContext& ctx,
                                                    ControlStateStruct arg0,
                                                    BoundLayout<KeccackNextRoundLayout> layout1) {
  // KeccackNextRound(zirgen/circuit/keccak2/top.zir:411)
  BoundLayout<KeccackNextRound_SuperLayout> x2 = LAYOUT_LOOKUP(layout1, _super);
  // KeccackNextRound(zirgen/circuit/keccak2/top.zir:409)
  Val x3 = arg0.round._super;
  // KeccackNextRound(zirgen/circuit/keccak2/top.zir:410)
  NondetRegStruct x4 = exec_IsZero(ctx, (x3 - Val(23)), LAYOUT_LOOKUP(layout1, isLast));
  Val x5 = x4._super;
  ControlStateStruct x6;
  if (to_size_t(x5)) {
    // KeccackNextRound(zirgen/circuit/keccak2/top.zir:412)
    ControlStateStruct x7 =
        exec_ControlState(ctx, Val(3), Val(0), Val(0), Val(0), LAYOUT_LOOKUP(x2, arm0));
    x6 = x7;
  } else if (to_size_t((Val(1) - x5))) {
    // KeccackNextRound(zirgen/circuit/keccak2/top.zir:414)
    ControlStateStruct x8 =
        exec_ControlState(ctx, Val(4), Val(0), Val(0), (x3 + Val(1)), LAYOUT_LOOKUP(x2, arm1));
    x6 = x8;
  } else {
    assert(0 && "Reached unreachable mux arm");
  }
  // KeccackNextRound(zirgen/circuit/keccak2/top.zir:411)
  ControlStateStruct x9 = back_ControlState(ctx, 0, LAYOUT_LOOKUP(x2, _super));
  return x9;
}
__device__ ControlStateStruct exec_ShaNextRound(ExecContext& ctx,
                                                ControlStateStruct arg0,
                                                BoundLayout<ShaNextRoundLayout> layout1) {
  // ShaNextRound(zirgen/circuit/keccak2/top.zir:420)
  BoundLayout<ShaNextRound_SuperLayout> x2 = LAYOUT_LOOKUP(layout1, _super);
  // ShaNextRound(zirgen/circuit/keccak2/top.zir:418)
  Val x3 = arg0.round._super;
  // ShaNextRound(zirgen/circuit/keccak2/top.zir:419)
  NondetRegStruct x4 = exec_IsZero(ctx, (x3 - Val(7)), LAYOUT_LOOKUP(layout1, isLast));
  Val x5 = x4._super;
  // ShaNextRound(zirgen/circuit/keccak2/top.zir:418)
  Val x6 = arg0.subType._super;
  Val x7 = arg0.block._super;
  ControlStateStruct x8;
  if (to_size_t(x5)) {
    // ShaNextRound(zirgen/circuit/keccak2/top.zir:421)
    ControlStateStruct x9 =
        exec_ControlState(ctx, Val(10), x6, x7, Val(0), LAYOUT_LOOKUP(x2, arm0));
    x8 = x9;
  } else if (to_size_t((Val(1) - x5))) {
    // ShaNextRound(zirgen/circuit/keccak2/top.zir:423)
    ControlStateStruct x10 =
        exec_ControlState(ctx, Val(9), x6, x7, (x3 + Val(1)), LAYOUT_LOOKUP(x2, arm1));
    x8 = x10;
  } else {
    assert(0 && "Reached unreachable mux arm");
  }
  // ShaNextRound(zirgen/circuit/keccak2/top.zir:420)
  ControlStateStruct x11 = back_ControlState(ctx, 0, LAYOUT_LOOKUP(x2, _super));
  return x11;
}
__device__ ControlStateStruct exec_ShaNextBlock(ExecContext& ctx,
                                                ControlStateStruct arg0,
                                                BoundLayout<ShaNextBlockLayout> layout1) {
  // ShaNextBlock(zirgen/circuit/keccak2/top.zir:432)
  BoundLayout<ShaNextBlock_SuperLayout> x2 = LAYOUT_LOOKUP(layout1, _super);
  // ShaNextBlock(zirgen/circuit/keccak2/top.zir:427)
  Val x3 = arg0.block._super;
  // ShaNextBlock(zirgen/circuit/keccak2/top.zir:428)
  NondetRegStruct x4 = exec_IsZero(ctx, (x3 - Val(3)), LAYOUT_LOOKUP(layout1, isLast));
  Val x5 = x4._super;
  // ShaNextBlock(zirgen/circuit/keccak2/top.zir:429)
  Val x6 = (Val(1) - x5);
  // ShaNextBlock(zirgen/circuit/keccak2/top.zir:427)
  Val x7 = arg0.subType._super;
  // ShaNextBlock(zirgen/circuit/keccak2/top.zir:430)
  NondetRegStruct x8 = exec_Reg(ctx, (x5 * (Val(1) - x7)), LAYOUT_LOOKUP(layout1, isSub0));
  Val x9 = x8._super;
  // ShaNextBlock(zirgen/circuit/keccak2/top.zir:431)
  Val x10 = ((Val(1) - x6) - x9);
  // ShaNextBlock(zirgen/circuit/keccak2/top.zir:432)
  BoundLayout<ShaNextBlock_SuperArm2_SuperLayout> x11 = LAYOUT_LOOKUP(x2, arm2);
  BoundLayout<ShaNextBlock_SuperArm2_Super_SuperLayout> x12 = LAYOUT_LOOKUP(x11, _super);
  ControlStateStruct x13;
  if (to_size_t(x6)) {
    // ShaNextBlock(zirgen/circuit/keccak2/top.zir:433)
    ControlStateStruct x14 =
        exec_ControlState(ctx, Val(9), x7, (x3 + Val(1)), Val(0), LAYOUT_LOOKUP(x2, arm0));
    x13 = x14;
  } else if (to_size_t(x9)) {
    // ShaNextBlock(zirgen/circuit/keccak2/top.zir:434)
    ControlStateStruct x15 =
        exec_ControlState(ctx, Val(2), Val(0), Val(0), Val(0), LAYOUT_LOOKUP(x2, arm1));
    x13 = x15;
  } else if (to_size_t(x10)) {
    // NextPreimage(zirgen/circuit/keccak2/top.zir:280)
    // ShaNextBlock(zirgen/circuit/keccak2/top.zir:436)
    Val x16 = INVOKE_EXTERN(ctx, nextPreimage);
    NondetRegStruct x17 = exec_NondetReg(ctx, x16, LAYOUT_LOOKUP(x11, more));
    Val x18 = x17._super;
    // AssertBit(zirgen/circuit/keccak2/bits.zir:6)
    // ShaNextBlock(zirgen/circuit/keccak2/top.zir:437)
    Val x19 = (Val(1) - x18);
    EQZ((x18 * x19),
        "loc(callsite( AssertBit ( zirgen/circuit/keccak2/bits.zir :6:20) at  ShaNextBlock ( "
        "zirgen/circuit/keccak2/top.zir :437:17)))");
    ControlStateStruct x20;
    if (to_size_t(x18)) {
      // ShaNextBlock(zirgen/circuit/keccak2/top.zir:439)
      ControlStateStruct x21 =
          exec_ControlState(ctx, Val(1), Val(0), Val(0), Val(0), LAYOUT_LOOKUP(x12, arm0));
      x20 = x21;
    } else if (to_size_t(x19)) {
      // ShaNextBlock(zirgen/circuit/keccak2/top.zir:441)
      ControlStateStruct x22 =
          exec_ControlState(ctx, Val(0), Val(0), Val(0), Val(0), LAYOUT_LOOKUP(x12, arm1));
      x20 = x22;
    } else {
      assert(0 && "Reached unreachable mux arm");
    }
    // ShaNextBlock(zirgen/circuit/keccak2/top.zir:438)
    ControlStateStruct x23 = back_ControlState(ctx, 0, LAYOUT_LOOKUP(x12, _super));
    x13 = x23;
  } else {
    assert(0 && "Reached unreachable mux arm");
  }
  // ShaNextBlock(zirgen/circuit/keccak2/top.zir:432)
  ControlStateStruct x24 = back_ControlState(ctx, 0, LAYOUT_LOOKUP(x2, _super));
  return x24;
}
__device__ ControlStateStruct
exec_ComputeCurrentStep(ExecContext& ctx,
                        Val12Array arg0,
                        ControlStateStruct arg1,
                        BoundLayout<ComputeCurrentStep_SuperLayout> layout2) {
  // ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:448)
  BoundLayout<ComputeCurrentStep_SuperArm2_SuperLayout> x3 = LAYOUT_LOOKUP(layout2, arm2);
  // ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:447)
  Val x4 = arg1.subType._super;
  Val x5 = arg1.round._super;
  ControlStateStruct x6;
  if (to_size_t(arg0[0])) {
    // ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:449)
    ControlStateStruct x7 =
        exec_ControlState(ctx, Val(0), Val(0), Val(0), Val(0), LAYOUT_LOOKUP(layout2, arm0));
    x6 = x7;
  } else if (to_size_t(arg0[1])) {
    // ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:450)
    ControlStateStruct x8 =
        exec_ControlState(ctx, Val(9), Val(0), Val(0), Val(0), LAYOUT_LOOKUP(layout2, arm1));
    x6 = x8;
  } else if (to_size_t(arg0[2])) {
    ControlStateStruct x9;
    if (to_size_t(x4)) {
      // ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:452)
      ControlStateStruct x10 =
          exec_ControlState(ctx, Val(4), Val(0), Val(0), Val(0), LAYOUT_LOOKUP(x3, arm0));
      x9 = x10;
    } else if (to_size_t((Val(1) - x4))) {
      // ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:454)
      ControlStateStruct x11 =
          exec_ControlState(ctx, Val(2), Val(1), Val(0), Val(0), LAYOUT_LOOKUP(x3, arm1));
      x9 = x11;
    } else {
      assert(0 && "Reached unreachable mux arm");
    }
    // ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:451)
    ControlStateStruct x12 = back_ControlState(ctx, 0, LAYOUT_LOOKUP(x3, _super));
    x6 = x12;
  } else if (to_size_t(arg0[3])) {
    // ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:456)
    ControlStateStruct x13 =
        exec_ControlState(ctx, Val(9), Val(1), Val(0), Val(0), LAYOUT_LOOKUP(layout2, arm3));
    x6 = x13;
  } else if (to_size_t(arg0[4])) {
    // ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:457)
    ControlStateStruct x14 =
        exec_ControlState(ctx, Val(5), Val(0), Val(0), x5, LAYOUT_LOOKUP(layout2, arm4));
    x6 = x14;
  } else if (to_size_t(arg0[5])) {
    // ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:458)
    ControlStateStruct x15 =
        exec_ControlState(ctx, Val(6), Val(0), Val(0), x5, LAYOUT_LOOKUP(layout2, arm5));
    x6 = x15;
  } else if (to_size_t(arg0[6])) {
    // ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:459)
    ControlStateStruct x16 =
        exec_ControlState(ctx, Val(7), Val(0), Val(0), x5, LAYOUT_LOOKUP(layout2, arm6));
    x6 = x16;
  } else if (to_size_t(arg0[7])) {
    // ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:460)
    ControlStateStruct x17 =
        exec_ControlState(ctx, Val(8), Val(0), Val(0), x5, LAYOUT_LOOKUP(layout2, arm7));
    x6 = x17;
  } else if (to_size_t(arg0[8])) {
    // ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:461)
    ControlStateStruct x18 = exec_KeccackNextRound(ctx, arg1, LAYOUT_LOOKUP(layout2, arm8));
    x6 = x18;
  } else if (to_size_t(arg0[9])) {
    // ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:462)
    ControlStateStruct x19 = exec_ShaNextRound(ctx, arg1, LAYOUT_LOOKUP(layout2, arm9));
    x6 = x19;
  } else if (to_size_t(arg0[10])) {
    // ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:463)
    ControlStateStruct x20 = exec_ShaNextBlock(ctx, arg1, LAYOUT_LOOKUP(layout2, arm10));
    x6 = x20;
  } else if (to_size_t(arg0[11])) {
    // ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:464)
    ControlStateStruct x21 =
        exec_ControlState(ctx, Val(1), Val(0), Val(0), Val(0), LAYOUT_LOOKUP(layout2, arm11));
    x6 = x21;
  } else {
    assert(0 && "Reached unreachable mux arm");
  }
  // ComputeCurrentStep(zirgen/circuit/keccak2/top.zir:448)
  ControlStateStruct x22 = back_ControlState(ctx, 0, LAYOUT_LOOKUP(layout2, _super));
  return x22;
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
  Val x6 = x2[0]._super._super;
  Val x7 = x2[1]._super._super;
  Val x8 = x2[2]._super._super;
  Val x9 = x2[3]._super._super;
  Val x10 = (((x6 + x7) + x8) + x9);
  Val x11 = x2[4]._super._super;
  Val x12 = x2[5]._super._super;
  Val x13 = x2[6]._super._super;
  Val x14 = (((x10 + x11) + x12) + x13);
  Val x15 = x2[7]._super._super;
  Val x16 = x2[8]._super._super;
  Val x17 = x2[9]._super._super;
  Val x18 = (((x14 + x15) + x16) + x17);
  Val x19 = x2[10]._super._super;
  Val x20 = x2[11]._super._super;
  Val x21 = (((x18 + x19) + x20) - Val(1));
  EQZ(x21, "OneHot(zirgen/circuit/keccak2/one_hot.zir:9)");
  // OneHot(zirgen/circuit/keccak2/one_hot.zir:11)
  Val x22 = (((x7 + (x8 * Val(2))) + (x9 * Val(3))) + (x11 * Val(4)));
  Val x23 = (((x22 + (x12 * Val(5))) + (x13 * Val(6))) + (x15 * Val(7)));
  Val x24 = (((x23 + (x16 * Val(8))) + (x17 * Val(9))) + (x19 * Val(10)));
  EQZ(((x24 + (x20 * Val(11))) - arg0), "OneHot(zirgen/circuit/keccak2/one_hot.zir:11)");
  return OneHot_12_Struct{.bits = x2};
}
__device__ WrapOneHotStruct back_WrapOneHot(ExecContext& ctx,
                                            Index distance0,
                                            BoundLayout<WrapOneHotLayout> layout1) {
  // WrapOneHot(zirgen/circuit/keccak2/top.zir:470)
  WrapOneHot_SuperStruct12Array x2 = map(
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
        NondetRegStruct x5 = back_Reg(ctx, distance0, x4);
        return WrapOneHot_SuperStruct{._super = x5};
      }));
  return WrapOneHotStruct{._super = x2};
}
__device__ WrapOneHotStruct exec_WrapOneHot(ExecContext& ctx,
                                            OneHot_12_Struct arg0,
                                            BoundLayout<WrapOneHotLayout> layout1) {
  WrapOneHot_SuperStruct12Array x2 = map(
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
        // WrapOneHot(zirgen/circuit/keccak2/top.zir:469)
        NondetRegStruct x5 = arg0.bits[to_size_t(x3)]._super;
        // WrapOneHot(zirgen/circuit/keccak2/top.zir:470)
        NondetRegStruct x6 = exec_Reg(ctx, x5._super, x4);
        return WrapOneHot_SuperStruct{._super = x6};
      }));
  return WrapOneHotStruct{._super = x2};
}
__device__ void step_Top(ExecContext& ctx, MutableBuf data0, GlobalBuf global1) {
  // Top(zirgen/circuit/keccak2/top.zir:473)
  BoundLayout<TopLayout> x2 = BIND_LAYOUT(kLayout_Top, data0);
  TopStruct x3 = exec_Top(ctx, x2, global1);
  return;
}
