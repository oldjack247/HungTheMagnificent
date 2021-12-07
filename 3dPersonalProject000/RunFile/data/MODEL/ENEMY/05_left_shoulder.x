xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 118;
 30.40731;-10.35535;0.04499;,
 29.79802;-11.49325;-0.33132;,
 21.98489;-4.67470;0.46611;,
 23.40954;-3.88622;0.50198;,
 25.21946;-12.11150;10.79698;,
 30.58650;-15.78509;8.00145;,
 29.79802;-11.49325;-0.33132;,
 29.79802;-16.74381;6.48719;,
 28.57051;-23.04268;10.76116;,
 28.39131;-23.04268;9.57841;,
 20.78426;-5.54381;10.55505;,
 22.20890;-16.22413;14.08532;,
 19.23418;-6.07246;9.11250;,
 15.00506;-8.43790;13.38642;,
 15.38138;-8.43790;14.93650;,
 17.19130;-19.63788;11.51379;,
 20.89178;-25.40813;8.58385;,
 21.48314;-25.14830;7.68785;,
 21.98489;-4.67470;0.46611;,
 11.43898;-13.33005;11.15538;,
 11.11642;-14.20813;12.25748;,
 8.53594;-17.88173;4.09491;,
 15.68602;-25.84718;2.45524;,
 16.80602;-25.14830;1.82804;,
 9.40506;-16.57356;3.62004;,
 16.80602;-25.14830;1.82804;,
 9.40506;-16.57356;3.62004;,
 26.86811;-18.84942;-6.74668;,
 22.60314;-24.96910;-3.44045;,
 16.71642;-19.10924;-0.92267;,
 21.98489;-13.07022;-5.37581;,
 29.88763;-16.74381;-3.67339;,
 24.87003;-10.62413;-1.80075;,
 25.70331;-13.15982;5.84209;,
 30.58650;-18.23118;1.80117;,
 29.70843;-20.68619;4.67729;,
 18.66074;-9.48623;-6.84523;,
 22.16410;-6.68173;-1.44233;,
 23.03322;-9.13679;7.49969;,
 21.07098;-18.41036;8.29714;,
 26.09754;-25.05870;4.97299;,
 16.71642;-19.10924;-0.92267;,
 22.60314;-24.96910;-3.44045;,
 15.27386;-12.98062;-6.65707;,
 5.73146;-2.65870;-8.69995;,
 7.98938;3.72979;-9.89163;,
 10.58778;9.93906;-2.44589;,
 8.24922;7.40338;11.52275;,
 17.35258;-14.20813;10.16979;,
 11.77050;-16.83341;-1.04811;,
 4.02906;-10.00591;-0.60012;,
 2.33562;-11.06317;-1.40652;,
 3.84986;-3.09774;-10.77867;,
 4.79066;5.12754;-11.32523;,
 5.66874;12.21491;-2.29356;,
 3.28538;9.84946;11.35250;,
 1.47546;-2.56909;13.47603;,
 4.40538;-3.96685;13.64628;,
 0.70490;-4.93455;-12.41837;,
 0.81242;4.68850;-12.13163;,
 -0.23590;13.79187;-1.86347;,
 -1.93830;10.98740;10.57300;,
 -2.81638;-2.39885;13.14453;,
 0.21210;-15.52526;-2.84907;,
 -0.32550;-14.64718;7.79535;,
 2.14745;-10.97359;8.69137;,
 3.58106;-10.88397;8.68242;,
 13.16826;-17.09325;6.27217;,
 11.77050;-16.83341;-1.04811;,
 2.33562;-11.06317;-1.40652;,
 4.02906;-10.00591;-0.60012;,
 0.21210;-15.52526;-2.84907;,
 17.97978;-23.66093;-0.17003;,
 16.06234;-20.85644;1.12917;,
 17.54970;-17.36205;-4.04971;,
 19.88826;-19.54828;-5.42058;,
 22.16410;-12.98062;-5.47434;,
 24.80730;-15.16685;-6.75564;,
 25.77499;-10.88397;-2.10540;,
 28.61530;-12.89997;-3.30602;,
 26.53659;-13.41966;5.40305;,
 28.96474;-15.95534;4.64148;,
 23.77690;-17.79213;9.08561;,
 26.16026;-20.33676;8.29714;,
 21.33082;-23.66093;5.90481;,
 19.16250;-20.85644;6.90832;,
 16.06234;-20.85644;1.12917;,
 17.97978;-23.66093;-0.17003;,
 25.11194;-5.19438;6.54991;,
 29.00954;-9.56686;4.87444;,
 29.79802;-8.69773;4.83859;,
 31.45562;-10.79438;-1.89037;,
 31.76027;-9.92526;-2.27564;,
 22.48666;-1.17132;-0.39404;,
 25.99002;-4.40589;6.39761;,
 21.69818;-1.78061;-0.15212;,
 19.43130;-7.12078;-7.08715;,
 19.18938;-7.81966;-6.04782;,
 16.36698;-12.72078;-7.84874;,
 25.70331;-12.98062;-6.56748;,
 26.16026;-12.63118;-7.40075;,
 20.08538;-16.13453;-8.45803;,
 16.44762;-12.98062;-8.87020;,
 12.22746;-15.87469;-5.21452;,
 12.89050;-15.34605;-4.53355;,
 7.32634;-17.09325;2.08788;,
 8.73306;-16.74381;2.15955;,
 20.23770;-16.13453;-7.42765;,
 17.52282;-21.29549;-4.46188;,
 17.17338;-21.99435;-5.09802;,
 15.03194;-26.80591;1.41587;,
 8.73306;-19.01964;8.84368;,
 9.64698;-18.15053;8.59280;,
 15.79354;-25.66798;1.44277;,
 15.24698;-24.01037;7.21295;,
 14.48538;-24.96910;7.44593;,
 12.20954;-21.90477;9.43506;,
 13.21306;-21.12523;9.14833;;
 
 165;
 3;0,1,2;,
 3;2,3,0;,
 3;0,3,4;,
 3;4,5,0;,
 3;6,0,5;,
 3;5,7,6;,
 3;7,5,8;,
 3;8,9,7;,
 3;3,10,4;,
 3;11,4,10;,
 3;4,11,8;,
 3;8,5,4;,
 3;12,10,3;,
 3;10,12,13;,
 3;13,14,10;,
 3;10,14,11;,
 3;15,11,14;,
 3;11,15,16;,
 3;16,8,11;,
 3;9,8,16;,
 3;16,17,9;,
 3;3,18,12;,
 3;14,13,19;,
 3;19,20,14;,
 3;14,20,15;,
 3;15,20,21;,
 3;22,15,21;,
 3;22,16,15;,
 3;17,16,22;,
 3;22,23,17;,
 3;20,19,24;,
 3;24,21,20;,
 3;25,22,21;,
 3;21,26,25;,
 3;27,28,29;,
 3;29,30,27;,
 3;31,27,30;,
 3;30,32,31;,
 3;31,32,33;,
 3;33,34,31;,
 3;33,35,34;,
 3;36,30,29;,
 3;30,36,37;,
 3;37,32,30;,
 3;32,37,38;,
 3;38,33,32;,
 3;39,33,38;,
 3;35,33,39;,
 3;39,40,35;,
 3;40,39,41;,
 3;41,42,40;,
 3;29,43,36;,
 3;36,43,44;,
 3;44,45,36;,
 3;37,36,45;,
 3;45,46,37;,
 3;37,46,47;,
 3;47,38,37;,
 3;48,38,47;,
 3;38,48,39;,
 3;49,43,29;,
 3;43,49,50;,
 3;50,44,43;,
 3;44,50,51;,
 3;51,52,44;,
 3;44,52,53;,
 3;53,45,44;,
 3;46,45,53;,
 3;53,54,46;,
 3;46,54,55;,
 3;55,47,46;,
 3;47,55,56;,
 3;56,57,47;,
 3;47,57,48;,
 3;58,52,51;,
 3;53,52,58;,
 3;58,59,53;,
 3;54,53,59;,
 3;59,60,54;,
 3;54,60,61;,
 3;61,55,54;,
 3;55,61,62;,
 3;62,56,55;,
 3;51,63,58;,
 3;56,62,64;,
 3;64,65,56;,
 3;56,65,66;,
 3;66,57,56;,
 3;48,57,66;,
 3;66,67,48;,
 3;67,39,48;,
 3;67,41,39;,
 3;41,67,68;,
 3;69,65,64;,
 3;65,69,70;,
 3;70,66,65;,
 3;67,66,70;,
 3;70,68,67;,
 3;64,71,69;,
 3;72,73,74;,
 3;74,75,72;,
 3;75,74,76;,
 3;76,77,75;,
 3;77,76,78;,
 3;78,79,77;,
 3;79,78,80;,
 3;80,81,79;,
 3;81,80,82;,
 3;82,83,81;,
 3;84,83,82;,
 3;82,85,84;,
 3;84,85,86;,
 3;86,87,84;,
 3;88,89,90;,
 3;90,89,91;,
 3;91,92,90;,
 3;90,92,93;,
 3;93,94,90;,
 3;90,94,88;,
 3;88,94,93;,
 3;93,95,88;,
 3;95,93,96;,
 3;96,97,95;,
 3;98,97,96;,
 3;92,91,99;,
 3;99,100,92;,
 3;93,92,100;,
 3;100,96,93;,
 3;96,100,101;,
 3;101,102,96;,
 3;96,102,98;,
 3;98,102,103;,
 3;103,104,98;,
 3;104,103,105;,
 3;105,106,104;,
 3;101,100,99;,
 3;99,107,101;,
 3;101,107,108;,
 3;108,109,101;,
 3;102,101,109;,
 3;109,103,102;,
 3;103,109,110;,
 3;110,105,103;,
 3;111,105,110;,
 3;105,111,112;,
 3;112,106,105;,
 3;110,109,108;,
 3;108,113,110;,
 3;110,113,114;,
 3;114,115,110;,
 3;110,115,111;,
 3;115,116,111;,
 3;111,116,117;,
 3;117,112,111;,
 3;115,114,117;,
 3;117,116,115;,
 3;61,60,62;,
 3;60,64,62;,
 3;60,59,64;,
 3;59,63,64;,
 3;59,58,63;,
 3;27,31,34;,
 3;35,27,34;,
 3;35,40,27;,
 3;40,28,27;;
 
 MeshMaterialList {
  1;
  165;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "C:\\Users\\student\\Desktop\\C++Game\\3dPersonalProject000\\3dPersonalProject000\\data\\TEXTURE\\chosen.png";
   }
  }
 }
 MeshNormals {
  172;
  0.057073;0.157701;-0.985836;,
  0.122049;0.252121;-0.959968;,
  -0.008692;0.061104;-0.998094;,
  0.643831;0.441215;0.625149;,
  0.628461;0.419907;0.654763;,
  0.921118;-0.322298;-0.218326;,
  0.796175;-0.582760;-0.162777;,
  0.579681;-0.809055;-0.096953;,
  0.601116;0.423259;0.677873;,
  0.210194;-0.091488;0.973370;,
  -0.420371;0.906035;0.048871;,
  -0.570648;0.809194;0.139876;,
  -0.717014;0.676895;0.166443;,
  -0.388840;-0.540438;0.746144;,
  -0.262750;-0.567647;0.780217;,
  0.308040;-0.936444;-0.167881;,
  -0.859569;0.488610;0.149668;,
  -0.859915;0.503104;0.086207;,
  -0.564222;-0.654447;0.503342;,
  -0.572324;-0.628927;0.526210;,
  0.377581;-0.875561;-0.301373;,
  -0.872040;0.487865;0.039174;,
  -0.487633;-0.164886;-0.857337;,
  -0.491451;-0.123273;-0.862136;,
  -0.205548;-0.451698;-0.868170;,
  -0.327120;-0.359153;-0.874072;,
  0.661734;0.659003;-0.357522;,
  0.757789;0.598107;-0.260814;,
  0.768744;0.410858;0.490132;,
  0.796621;0.515417;0.315817;,
  0.539027;0.070177;0.839360;,
  0.255862;-0.215898;-0.942296;,
  0.773133;0.534087;-0.342077;,
  0.810113;0.579757;0.087170;,
  0.296221;-0.167471;0.940323;,
  0.330180;-0.210442;0.920161;,
  -0.162944;-0.550373;-0.818865;,
  0.317343;-0.431940;-0.844228;,
  0.492938;0.203274;-0.845985;,
  0.600370;0.768855;-0.220039;,
  0.672629;0.713921;0.194647;,
  0.067065;-0.307458;0.949195;,
  -0.517044;-0.790433;-0.328453;,
  -0.479865;-0.818957;-0.314705;,
  0.751116;-0.618456;-0.230949;,
  0.661921;-0.403592;-0.631645;,
  0.432183;0.258360;-0.863984;,
  0.256148;0.940343;-0.223928;,
  0.342127;0.913655;0.219507;,
  0.001436;-0.210218;0.977654;,
  -0.050255;-0.230513;0.971771;,
  0.619652;-0.296654;-0.726655;,
  0.140198;0.564395;-0.813513;,
  0.236034;0.945252;-0.225360;,
  0.223819;0.948812;0.222848;,
  -0.089880;-0.014390;0.995849;,
  0.910914;-0.395422;-0.117804;,
  0.138372;-0.438331;0.888098;,
  0.290740;-0.826575;0.481916;,
  -0.181481;-0.561227;0.807520;,
  -0.428881;-0.849631;0.306900;,
  -0.821169;-0.513859;-0.248253;,
  -0.795644;-0.597712;0.098445;,
  -0.688480;-0.217671;-0.691819;,
  -0.521275;-0.054507;-0.851646;,
  -0.190742;0.342709;-0.919874;,
  0.032559;0.546959;-0.836526;,
  0.398876;0.804163;-0.440704;,
  0.594004;0.797492;-0.105667;,
  0.678703;0.603167;0.418989;,
  0.653598;0.432616;0.621010;,
  0.559769;0.293726;0.774844;,
  0.562669;0.286764;0.775352;,
  -0.444798;-0.578100;0.684072;,
  -0.440210;-0.584306;0.681763;,
  0.246508;-0.138800;0.959150;,
  0.514779;-0.436581;0.737835;,
  0.605145;-0.311275;0.732739;,
  0.868747;-0.494371;0.029598;,
  0.932134;0.298031;0.205678;,
  0.612976;0.689113;-0.386501;,
  0.736081;0.674358;-0.058529;,
  -0.735372;0.670251;0.099959;,
  -0.849199;0.518711;-0.098991;,
  -0.907422;0.414738;0.067666;,
  -0.774378;0.627001;-0.084903;,
  0.564270;-0.797351;-0.214083;,
  0.503224;-0.859997;-0.084678;,
  0.032803;-0.025534;-0.999136;,
  -0.157605;-0.218922;-0.962930;,
  -0.598921;0.787405;-0.145904;,
  -0.457232;0.887856;-0.051486;,
  -0.409554;0.905174;0.113695;,
  -0.245501;0.958279;0.146393;,
  0.697649;-0.708978;-0.103132;,
  0.869852;-0.487033;-0.078468;,
  0.898643;-0.438521;-0.011869;,
  -0.737847;-0.622045;-0.261995;,
  -0.712828;-0.682235;0.162577;,
  -0.432785;0.852564;0.292969;,
  0.830142;-0.556437;0.035240;,
  0.749623;-0.467943;0.468074;,
  0.619667;-0.360795;0.697021;,
  -0.633745;-0.693332;0.343012;,
  0.277728;0.017004;0.960509;,
  0.642083;0.644544;0.415081;,
  0.714312;0.602593;0.355866;,
  0.894074;-0.358112;-0.269049;,
  0.881908;-0.379906;-0.279123;,
  0.897362;-0.354282;-0.263108;,
  0.392664;-0.058634;0.917811;,
  -0.393661;0.915238;0.085850;,
  -0.427612;0.903693;0.022095;,
  0.024150;-0.111965;0.993419;,
  0.282285;-0.955841;-0.081747;,
  -0.483958;0.875001;-0.012513;,
  -0.382048;-0.531032;0.756337;,
  0.306637;-0.927016;-0.215904;,
  -0.830814;0.556415;0.012233;,
  -0.373567;-0.139052;-0.917122;,
  -0.397737;-0.171486;-0.901331;,
  -0.348692;-0.106356;-0.931183;,
  0.403798;0.519776;-0.752848;,
  0.513086;0.475382;-0.714671;,
  0.679548;0.370726;-0.633069;,
  0.430146;0.015619;0.902624;,
  -0.639482;-0.705424;0.305678;,
  -0.445298;-0.852135;0.274910;,
  -0.489622;-0.845441;0.213309;,
  -0.626334;-0.737603;0.252283;,
  0.187082;0.126608;0.974151;,
  0.591039;-0.774355;-0.225935;,
  -0.042119;0.178352;0.983065;,
  -0.103272;0.194173;0.975516;,
  0.827067;-0.561732;0.020395;,
  0.860396;-0.507034;0.051338;,
  -0.262730;-0.959311;-0.103423;,
  -0.153358;-0.420695;0.894146;,
  -0.145842;-0.423732;0.893969;,
  0.715821;0.698272;0.004177;,
  0.266245;-0.111558;0.957428;,
  -0.441106;0.694101;0.568902;,
  -0.493086;0.658855;0.568134;,
  -0.562441;0.770808;0.299191;,
  0.608255;-0.711458;-0.351929;,
  0.389139;0.568104;-0.725141;,
  0.313393;0.448272;-0.837160;,
  0.264265;0.306875;-0.914326;,
  -0.771155;0.599799;-0.213452;,
  0.715296;-0.694964;-0.073327;,
  -0.446527;-0.437679;-0.780417;,
  -0.591110;-0.470739;-0.654976;,
  -0.759978;-0.583064;-0.287174;,
  -0.600417;0.727323;0.332415;,
  0.843934;-0.531311;0.074053;,
  -0.666450;-0.702816;0.248784;,
  0.053372;0.253312;0.965911;,
  0.262563;0.016859;0.964768;,
  0.043982;0.234102;0.971217;,
  -0.991132;0.040714;-0.126493;,
  -0.987661;-0.022559;-0.154975;,
  -0.981131;-0.021716;-0.192123;,
  -0.990954;-0.034119;-0.129790;,
  -0.998407;-0.001864;-0.056395;,
  -0.998971;0.009276;-0.044405;,
  -0.999208;0.012292;-0.037853;,
  0.724962;-0.628339;-0.282169;,
  0.718812;-0.642203;-0.266242;,
  0.734290;-0.620852;-0.274519;,
  0.739893;-0.610697;-0.282148;,
  0.715490;-0.635699;-0.289761;,
  0.700230;-0.648867;-0.297741;;
  165;
  3;0,1,0;,
  3;0,2,0;,
  3;105,106,3;,
  3;3,4,105;,
  3;107,108,109;,
  3;109,5,107;,
  3;5,109,6;,
  3;6,7,5;,
  3;106,8,3;,
  3;9,3,8;,
  3;3,9,110;,
  3;110,4,3;,
  3;10,111,112;,
  3;111,10,11;,
  3;11,12,111;,
  3;8,113,9;,
  3;13,9,113;,
  3;9,13,14;,
  3;14,110,9;,
  3;7,6,114;,
  3;114,15,7;,
  3;112,115,10;,
  3;12,11,16;,
  3;16,17,12;,
  3;113,116,13;,
  3;13,116,18;,
  3;19,13,18;,
  3;19,14,13;,
  3;15,114,117;,
  3;117,20,15;,
  3;17,16,21;,
  3;21,118,17;,
  3;119,120,119;,
  3;119,121,119;,
  3;22,23,24;,
  3;24,25,22;,
  3;26,122,123;,
  3;123,27,26;,
  3;26,27,28;,
  3;28,29,26;,
  3;28,30,29;,
  3;31,25,24;,
  3;123,124,32;,
  3;32,27,123;,
  3;27,32,33;,
  3;33,28,27;,
  3;34,28,125;,
  3;30,28,34;,
  3;34,35,30;,
  3;126,127,128;,
  3;128,129,126;,
  3;24,36,31;,
  3;31,36,37;,
  3;37,38,31;,
  3;32,31,38;,
  3;38,39,32;,
  3;32,39,40;,
  3;40,33,32;,
  3;41,125,130;,
  3;125,41,34;,
  3;42,36,24;,
  3;36,42,43;,
  3;43,37,36;,
  3;37,131,44;,
  3;44,45,37;,
  3;37,45,46;,
  3;46,38,37;,
  3;39,38,46;,
  3;46,47,39;,
  3;39,47,48;,
  3;48,40,39;,
  3;130,132,49;,
  3;49,50,130;,
  3;130,50,41;,
  3;51,45,44;,
  3;46,45,51;,
  3;51,52,46;,
  3;47,46,52;,
  3;52,53,47;,
  3;47,53,54;,
  3;54,48,47;,
  3;132,133,55;,
  3;55,49,132;,
  3;44,56,51;,
  3;49,55,57;,
  3;57,58,49;,
  3;49,58,59;,
  3;59,50,49;,
  3;41,50,59;,
  3;59,60,41;,
  3;60,34,41;,
  3;60,128,127;,
  3;128,60,42;,
  3;44,134,135;,
  3;58,44,131;,
  3;43,136,58;,
  3;60,136,43;,
  3;43,42,60;,
  3;135,56,44;,
  3;61,62,63;,
  3;63,64,61;,
  3;64,63,65;,
  3;65,66,64;,
  3;66,65,67;,
  3;67,68,66;,
  3;68,67,69;,
  3;69,70,68;,
  3;70,69,71;,
  3;71,72,70;,
  3;73,137,138;,
  3;138,74,73;,
  3;73,74,62;,
  3;62,61,73;,
  3;75,76,77;,
  3;77,76,78;,
  3;78,79,77;,
  3;139,79,80;,
  3;80,81,139;,
  3;77,140,75;,
  3;141,142,143;,
  3;143,82,141;,
  3;82,143,83;,
  3;83,84,82;,
  3;85,84,83;,
  3;144,78,86;,
  3;86,87,144;,
  3;80,145,146;,
  3;146,147,80;,
  3;147,146,88;,
  3;88,89,147;,
  3;83,148,85;,
  3;85,148,90;,
  3;90,91,85;,
  3;91,90,92;,
  3;92,93,91;,
  3;149,87,86;,
  3;86,94,149;,
  3;149,94,95;,
  3;95,96,149;,
  3;89,88,150;,
  3;150,151,89;,
  3;151,150,97;,
  3;97,152,151;,
  3;98,152,97;,
  3;92,153,99;,
  3;99,93,92;,
  3;154,96,95;,
  3;95,100,154;,
  3;154,100,101;,
  3;101,102,154;,
  3;97,155,98;,
  3;155,103,98;,
  3;156,157,104;,
  3;104,158,156;,
  3;102,101,104;,
  3;104,157,102;,
  3;159,160,161;,
  3;160,162,161;,
  3;160,163,162;,
  3;163,164,162;,
  3;163,165,164;,
  3;166,167,168;,
  3;169,166,168;,
  3;169,170,166;,
  3;170,171,166;;
 }
 MeshTextureCoords {
  118;
  0.322725;0.157890;,
  0.324704;0.156935;,
  0.325904;0.189058;,
  0.323505;0.187983;,
  0.305035;0.169474;,
  0.308063;0.148457;,
  0.323385;0.153830;,
  0.308753;0.144755;,
  0.296699;0.140217;,
  0.296669;0.137112;,
  0.307493;0.193118;,
  0.296699;0.168757;,
  0.307853;0.197297;,
  0.297329;0.201596;,
  0.297179;0.197417;,
  0.287524;0.170071;,
  0.285065;0.147621;,
  0.284645;0.144277;,
  0.323985;0.193237;,
  0.286265;0.198849;,
  0.286595;0.194551;,
  0.272067;0.188699;,
  0.272892;0.152994;,
  0.272502;0.148457;,
  0.271617;0.194312;,
  0.270823;0.152278;,
  0.269459;0.188938;,
  0.525838;0.396480;,
  0.531115;0.418930;,
  0.519601;0.430633;,
  0.513364;0.402212;,
  0.524159;0.382628;,
  0.511205;0.384539;,
  0.512405;0.358506;,
  0.524399;0.365432;,
  0.525358;0.353969;,
  0.505449;0.408183;,
  0.503530;0.386211;,
  0.504729;0.357312;,
  0.513844;0.334146;,
  0.527757;0.335101;,
  0.516962;0.304770;,
  0.530156;0.310263;,
  0.507847;0.421557;,
  0.487578;0.437320;,
  0.480262;0.420602;,
  0.475704;0.394331;,
  0.473785;0.356357;,
  0.504969;0.331758;,
  0.513604;0.439947;,
  0.502090;0.457859;,
  0.500891;0.463352;,
  0.484460;0.444246;,
  0.475344;0.426572;,
  0.468748;0.395764;,
  0.466349;0.355879;,
  0.474625;0.320055;,
  0.479662;0.322921;,
  0.482421;0.455471;,
  0.471267;0.436126;,
  0.459753;0.398152;,
  0.458313;0.354446;,
  0.468388;0.312651;,
  0.499691;0.477682;,
  0.484820;0.278738;,
  0.486379;0.294023;,
  0.488537;0.298322;,
  0.507128;0.312174;,
  0.509047;0.297127;,
  0.495614;0.279932;,
  0.496333;0.284708;,
  0.493935;0.263453;,
  0.502330;0.131261;,
  0.507607;0.131261;,
  0.507607;0.150964;,
  0.502330;0.150964;,
  0.507607;0.172101;,
  0.502330;0.172101;,
  0.507607;0.190610;,
  0.502330;0.190610;,
  0.507607;0.218672;,
  0.502330;0.218672;,
  0.507607;0.238256;,
  0.502330;0.238256;,
  0.502330;0.253899;,
  0.507607;0.253899;,
  0.507607;0.269662;,
  0.502330;0.269662;,
  0.410699;0.144516;,
  0.410099;0.163025;,
  0.408420;0.161831;,
  0.399545;0.178071;,
  0.399065;0.175206;,
  0.399545;0.132336;,
  0.409020;0.145352;,
  0.399545;0.129589;,
  0.385032;0.138068;,
  0.384313;0.134246;,
  0.374418;0.139859;,
  0.384792;0.172578;,
  0.385632;0.169712;,
  0.374478;0.161353;,
  0.374418;0.143083;,
  0.365003;0.141172;,
  0.365363;0.137709;,
  0.352470;0.136874;,
  0.352709;0.133172;,
  0.374358;0.164697;,
  0.364763;0.169115;,
  0.364163;0.166488;,
  0.353309;0.170429;,
  0.344974;0.144397;,
  0.343654;0.142605;,
  0.353489;0.173534;,
  0.345333;0.166608;,
  0.346473;0.164458;,
  0.344374;0.155144;,
  0.342815;0.156099;;
 }
}