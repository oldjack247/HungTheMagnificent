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
 114;
 7.94119;-10.06637;3.10847;,
 6.05959;-6.82286;4.30014;,
 6.49863;-6.91246;5.33054;,
 8.38023;-10.23661;4.11198;,
 7.01831;-11.37453;5.00799;,
 5.18151;-8.31022;6.19967;,
 3.04006;-13.48014;3.62816;,
 0.71943;-10.76525;5.07966;,
 0.06535;-14.43884;0.34879;,
 -2.55993;-11.81357;1.59422;,
 -1.02777;-13.91021;-3.45921;,
 -3.51865;-11.11470;-2.59907;,
 1.81255;-5.16525;-8.88001;,
 4.08839;-8.31022;-9.46241;,
 3.69415;-8.48941;-10.37631;,
 1.38247;-5.25484;-9.79393;,
 -0.46329;-6.56301;-10.35840;,
 2.08135;-9.44813;-10.96768;,
 -3.63513;-10.32621;-4.65986;,
 -0.98297;-13.39054;-5.58274;,
 -2.07609;-15.83660;-0.50241;,
 -4.45945;-13.04110;0.44733;,
 -4.44153;-2.19053;-8.36929;,
 4.61703;-13.73997;-10.64512;,
 2.99527;-15.31694;-8.34241;,
 -5.79449;-4.98606;-6.01281;,
 2.20679;-16.71470;-4.85698;,
 -6.82489;-7.17229;-1.30882;,
 3.25510;-17.41357;-1.24610;,
 -6.01849;-7.53069;3.21597;,
 -2.25529;-6.56301;6.46846;,
 5.88040;-16.62510;1.55838;,
 8.89991;-15.66637;3.09951;,
 1.73191;-3.41804;7.59742;,
 9.16871;-13.04110;-11.77408;,
 5.31591;-13.56079;-11.49632;,
 -4.09209;-3.05965;-9.68641;,
 -0.98297;2.62099;-8.64705;,
 12.61832;-12.86190;-10.04480;,
 1.59751;7.43251;-6.03074;,
 14.63431;-13.21133;-6.59522;,
 3.29991;10.75667;-0.95042;,
 4.43783;5.94515;3.15325;,
 14.72392;-13.56079;-2.55425;,
 2.29639;-4.63662;8.44863;,
 9.86759;-15.39758;3.03677;,
 7.89639;-2.10093;3.87006;,
 7.85159;-3.58829;2.40958;,
 7.41255;-1.22285;2.15870;,
 6.36423;-3.67789;4.02238;,
 5.96999;-1.31244;3.89694;,
 11.26535;-8.65966;2.31102;,
 11.26535;-10.15598;0.85952;,
 10.78152;-7.96077;0.51005;,
 9.77799;-10.15598;2.56190;,
 9.33895;-7.96077;2.28414;,
 14.19527;-10.23661;-6.59522;,
 13.23656;-11.81357;-7.40162;,
 12.26887;-9.79757;-6.89090;,
 14.10567;-11.90317;-5.26017;,
 13.14696;-9.88717;-4.75842;,
 7.94119;-8.65966;-11.19169;,
 6.58823;-8.05037;-9.86559;,
 8.85511;-8.22957;-9.39074;,
 6.45384;-10.15598;-10.71680;,
 8.72967;-10.41581;-10.25087;,
 11.05031;-3.32844;-4.45378;,
 10.12744;-4.72621;-5.34083;,
 8.89991;-2.71020;-4.83010;,
 10.56647;-4.98606;-3.46818;,
 9.64360;-2.97901;-2.75138;,
 6.05959;0.34516;-7.96609;,
 4.78727;-1.49164;-8.10944;,
 3.82855;0.69459;-7.52706;,
 6.31943;-0.96302;-6.67586;,
 5.36071;1.04403;-5.95009;,
 6.22983;5.24627;-2.71553;,
 5.62055;3.75891;-3.67425;,
 4.26759;5.59571;-3.93410;,
 5.79975;4.28755;-1.43426;,
 4.57223;6.21395;-1.59553;,
 3.25510;-14.78830;-8.19252;,
 9.21351;-15.57677;1.88747;,
 0.54919;-12.42286;-1.62483;,
 8.50567;-7.17229;1.01834;,
 9.21351;-15.57677;1.88747;,
 11.96424;-12.51246;-1.69651;,
 4.52744;-10.76525;3.45549;,
 -3.16921;0.78419;9.43181;,
 -8.59897;-2.28013;3.24938;,
 0.54919;-12.42286;-1.62483;,
 9.21351;-15.57677;1.88747;,
 1.11367;7.17267;5.71337;,
 8.03079;-5.51470;-5.72852;,
 -0.37369;9.44851;-2.96885;,
 -4.63865;5.86451;-6.10484;,
 4.48263;-7.09165;-8.63159;,
 -8.20473;1.13363;-3.98133;,
 10.61127;-11.55374;-8.64951;,
 11.96424;-12.51246;-1.69651;,
 6.22983;-12.77229;-9.85013;,
 10.61127;-11.55374;-8.64951;,
 6.22983;-12.77229;-9.85013;,
 3.25510;-14.78830;-8.19252;,
 1.15847;-9.88717;-7.34133;,
 0.54919;-12.42286;-1.62483;,
 -8.59897;-2.28013;3.24938;,
 -8.20473;1.13363;-3.98133;,
 0.19975;-0.08493;0.03277;,
 -4.63865;5.86451;-6.10484;,
 -8.59897;-2.28013;3.24938;,
 -3.16921;0.78419;9.43181;,
 1.11367;7.17267;5.71337;,
 -0.37369;9.44851;-2.96885;;
 
 98;
 3;0,1,2;,
 3;2,3,0;,
 3;4,3,2;,
 3;2,5,4;,
 3;6,4,5;,
 3;5,7,6;,
 3;8,6,7;,
 3;7,9,8;,
 3;10,8,9;,
 3;9,11,10;,
 3;12,13,14;,
 3;14,15,12;,
 3;16,15,14;,
 3;14,17,16;,
 3;18,16,17;,
 3;17,19,18;,
 3;18,19,20;,
 3;20,21,18;,
 3;22,23,24;,
 3;24,25,22;,
 3;25,24,26;,
 3;26,27,25;,
 3;27,26,28;,
 3;28,29,27;,
 3;30,29,28;,
 3;28,31,30;,
 3;30,31,32;,
 3;32,33,30;,
 3;34,35,36;,
 3;36,37,34;,
 3;38,34,37;,
 3;37,39,38;,
 3;40,38,39;,
 3;39,41,40;,
 3;40,41,42;,
 3;42,43,40;,
 3;43,42,44;,
 3;44,45,43;,
 3;46,47,48;,
 3;46,49,47;,
 3;46,50,49;,
 3;46,48,50;,
 3;51,52,53;,
 3;51,54,52;,
 3;51,55,54;,
 3;51,53,55;,
 3;56,57,58;,
 3;56,59,57;,
 3;56,60,59;,
 3;56,58,60;,
 3;61,62,63;,
 3;61,64,62;,
 3;61,65,64;,
 3;61,63,65;,
 3;66,67,68;,
 3;66,69,67;,
 3;66,70,69;,
 3;66,68,70;,
 3;71,72,73;,
 3;71,74,72;,
 3;71,75,74;,
 3;71,73,75;,
 3;76,77,78;,
 3;76,79,77;,
 3;76,80,79;,
 3;76,78,80;,
 3;81,82,83;,
 3;84,85,86;,
 3;84,87,85;,
 3;88,87,84;,
 3;87,88,89;,
 3;89,90,87;,
 3;87,90,91;,
 3;84,92,88;,
 3;92,84,93;,
 3;93,94,92;,
 3;95,94,93;,
 3;93,96,95;,
 3;97,95,96;,
 3;98,93,84;,
 3;84,99,98;,
 3;100,96,93;,
 3;93,101,100;,
 3;96,102,103;,
 3;103,104,96;,
 3;96,104,97;,
 3;97,104,105;,
 3;105,106,97;,
 3;104,81,105;,
 3;107,108,109;,
 3;110,108,107;,
 3;111,108,110;,
 3;108,111,112;,
 3;113,108,112;,
 3;108,113,109;,
 3;98,86,82;,
 3;82,81,98;,
 3;81,100,98;;
 
 MeshMaterialList {
  1;
  98;
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
    "C:\\Users\\student\\Desktop\\C++Game\\3dPersonalProject000\\3dPersonalProject000\\data\\TEXTURE\\Enemy\\chosen.png";
   }
  }
 }
 MeshNormals {
  116;
  0.789213;0.551427;-0.270317;,
  0.780372;0.557069;-0.284065;,
  0.797818;0.545619;-0.256487;,
  0.357313;-0.144524;0.922735;,
  0.169775;-0.306296;0.936674;,
  -0.173474;-0.535769;0.826353;,
  -0.282417;-0.634376;0.719589;,
  -0.526054;-0.726490;0.442131;,
  -0.635586;-0.727288;0.259002;,
  -0.709595;-0.700552;0.075512;,
  -0.736792;-0.673783;0.056159;,
  0.706036;0.581549;-0.404121;,
  0.698584;0.582483;-0.415565;,
  0.461528;0.481178;-0.745292;,
  0.461476;0.465755;-0.755058;,
  0.130750;0.290989;-0.947750;,
  0.147646;0.327318;-0.933308;,
  -0.709160;-0.465008;-0.529961;,
  -0.711107;-0.453700;-0.537105;,
  -0.753803;-0.518155;-0.404100;,
  -0.760815;-0.514085;-0.396077;,
  -0.609701;-0.346887;-0.712695;,
  -0.629947;-0.358309;-0.689043;,
  -0.666551;-0.420788;-0.615343;,
  -0.702677;-0.483498;-0.521992;,
  -0.750212;-0.612290;-0.249566;,
  -0.740130;-0.666062;-0.092572;,
  -0.595319;-0.714801;0.366953;,
  -0.582812;-0.718372;0.379831;,
  -0.273434;-0.575187;0.770969;,
  -0.340335;-0.620106;0.706852;,
  -0.111686;-0.462386;0.879617;,
  0.004184;-0.342556;0.939488;,
  0.100791;0.241462;-0.965162;,
  -0.084369;0.095364;-0.991861;,
  -0.049124;0.141531;-0.988714;,
  0.226215;0.319474;-0.920197;,
  0.507421;0.437315;-0.742482;,
  0.617933;0.452497;-0.642966;,
  0.859834;0.473974;-0.189827;,
  0.870884;0.455384;-0.184896;,
  0.880169;0.360487;0.308790;,
  0.826270;0.288495;0.483785;,
  0.720223;0.175422;0.671197;,
  0.717372;0.164226;0.677058;,
  0.968367;0.159370;-0.192008;,
  0.379078;-0.283216;0.880959;,
  0.038175;0.059261;0.997512;,
  0.964961;0.182697;-0.188339;,
  0.634791;-0.538001;0.554613;,
  0.034128;0.132171;0.990639;,
  0.217316;0.336439;-0.916287;,
  0.866465;-0.339674;-0.365868;,
  0.852276;0.298367;0.429654;,
  0.136578;0.945642;-0.295140;,
  -0.577000;0.337495;-0.743753;,
  0.135798;-0.419794;-0.897403;,
  0.265481;0.385519;-0.883683;,
  0.873449;-0.410580;-0.261747;,
  0.777224;0.138139;0.613874;,
  -0.161327;0.187369;-0.968951;,
  0.690913;-0.433428;-0.578601;,
  0.910930;0.366935;0.188587;,
  0.480804;0.650809;-0.587601;,
  0.541721;0.287271;-0.789945;,
  0.921068;-0.388981;0.018114;,
  0.665921;0.472651;0.577192;,
  -0.720646;-0.691654;-0.047800;,
  -0.449858;-0.804925;0.386940;,
  -0.711937;-0.697184;0.084140;,
  0.810637;0.270193;0.519484;,
  0.860152;0.389943;0.328759;,
  0.497958;0.036363;0.866439;,
  0.584059;-0.001317;0.811710;,
  -0.431528;-0.652437;0.622984;,
  0.879084;0.367556;0.303503;,
  0.728459;0.501408;-0.466838;,
  0.870130;0.492417;-0.019987;,
  0.139769;0.262903;-0.954645;,
  0.062993;0.219296;-0.973623;,
  -0.639259;-0.340953;-0.689274;,
  0.877294;0.479241;-0.026122;,
  0.042640;0.309987;-0.949784;,
  -0.676097;-0.255882;-0.690954;,
  -0.396855;0.764956;0.507295;,
  0.547688;0.003306;0.836676;,
  0.547969;0.003352;0.836492;,
  -0.638959;-0.428666;-0.638731;,
  -0.649843;-0.402230;-0.644915;,
  0.626315;-0.555713;0.546729;,
  0.359873;0.867518;0.343370;,
  0.325608;0.907679;0.264762;,
  0.229725;0.971769;-0.053763;,
  0.869846;0.136590;-0.474036;,
  0.271814;0.961967;0.027152;,
  0.090157;0.950248;-0.298160;,
  0.334873;0.899275;-0.281362;,
  0.590389;0.132065;0.796241;,
  -0.446616;-0.653537;0.611084;,
  -0.411182;-0.619861;0.668357;,
  0.343116;0.353238;-0.870341;,
  -0.453833;-0.037454;-0.890299;,
  0.109194;0.470247;-0.875754;,
  -0.435320;0.018081;-0.900094;,
  -0.775499;-0.553546;-0.303623;,
  -0.186093;0.761550;0.620815;,
  -0.502000;0.388753;0.772572;,
  -0.198603;0.972641;0.120526;,
  -0.635164;0.714349;-0.293721;,
  -0.976214;0.195801;-0.093100;,
  -0.880249;0.093523;0.465205;,
  0.437390;-0.844829;-0.308146;,
  0.582814;-0.781913;-0.221223;,
  0.480214;-0.838795;-0.256551;,
  0.359171;-0.865996;-0.347918;,
  0.346498;-0.845439;-0.406414;;
  98;
  3;0,1,0;,
  3;0,2,0;,
  3;3,85,86;,
  3;86,4,3;,
  3;5,3,4;,
  3;4,6,5;,
  3;7,5,6;,
  3;6,8,7;,
  3;9,7,8;,
  3;8,10,9;,
  3;11,12,13;,
  3;13,14,11;,
  3;15,14,13;,
  3;13,16,15;,
  3;17,87,88;,
  3;88,18,17;,
  3;17,18,19;,
  3;19,20,17;,
  3;21,22,23;,
  3;23,24,21;,
  3;24,23,25;,
  3;25,26,24;,
  3;26,25,27;,
  3;27,28,26;,
  3;29,28,27;,
  3;27,30,29;,
  3;29,30,31;,
  3;31,32,29;,
  3;33,34,35;,
  3;35,36,33;,
  3;37,33,36;,
  3;36,38,37;,
  3;39,37,38;,
  3;38,40,39;,
  3;39,40,41;,
  3;41,42,39;,
  3;42,41,43;,
  3;43,44,42;,
  3;45,45,45;,
  3;46,46,89;,
  3;46,47,46;,
  3;90,90,90;,
  3;48,48,48;,
  3;49,49,49;,
  3;50,50,50;,
  3;91,91,91;,
  3;51,51,51;,
  3;52,52,52;,
  3;53,53,53;,
  3;92,92,92;,
  3;54,54,54;,
  3;55,55,55;,
  3;56,56,56;,
  3;93,93,93;,
  3;57,57,57;,
  3;58,58,58;,
  3;59,59,59;,
  3;94,94,94;,
  3;60,60,60;,
  3;61,61,61;,
  3;62,62,62;,
  3;95,95,95;,
  3;63,64,63;,
  3;65,65,65;,
  3;66,66,66;,
  3;63,63,96;,
  3;67,68,69;,
  3;70,97,71;,
  3;70,72,97;,
  3;73,72,70;,
  3;98,99,74;,
  3;74,69,98;,
  3;98,69,68;,
  3;70,75,73;,
  3;75,70,76;,
  3;76,77,75;,
  3;78,100,100;,
  3;76,79,78;,
  3;80,78,101;,
  3;81,76,70;,
  3;70,71,81;,
  3;82,79,76;,
  3;76,102,82;,
  3;101,82,103;,
  3;103,83,79;,
  3;79,83,80;,
  3;80,83,69;,
  3;69,104,80;,
  3;83,67,69;,
  3;105,84,106;,
  3;107,84,105;,
  3;108,84,107;,
  3;109,108,109;,
  3;110,109,109;,
  3;84,110,106;,
  3;111,112,113;,
  3;113,114,111;,
  3;114,115,111;;
 }
 MeshTextureCoords {
  114;
  0.487700;0.164940;,
  0.488060;0.176280;,
  0.486500;0.176400;,
  0.486140;0.165180;,
  0.483260;0.165410;,
  0.483620;0.176400;,
  0.476540;0.165530;,
  0.476180;0.177000;,
  0.470430;0.164820;,
  0.469590;0.176520;,
  0.464070;0.162550;,
  0.462750;0.173890;,
  0.464310;0.149650;,
  0.465270;0.137230;,
  0.466710;0.137950;,
  0.465750;0.149890;,
  0.468630;0.150610;,
  0.468990;0.138540;,
  0.480260;0.151320;,
  0.480140;0.139620;,
  0.489020;0.141410;,
  0.488900;0.149170;,
  0.455310;0.139500;,
  0.451960;0.183680;,
  0.447280;0.181650;,
  0.449440;0.141050;,
  0.441640;0.180220;,
  0.441760;0.139980;,
  0.436130;0.180820;,
  0.435290;0.138780;,
  0.428090;0.141290;,
  0.430370;0.182010;,
  0.425330;0.184880;,
  0.420530;0.141770;,
  0.383110;0.113350;,
  0.377720;0.109650;,
  0.372380;0.068210;,
  0.380360;0.057280;,
  0.388630;0.116390;,
  0.387430;0.046980;,
  0.394510;0.117650;,
  0.395230;0.037130;,
  0.402540;0.049160;,
  0.400500;0.116450;,
  0.417060;0.070720;,
  0.411900;0.112270;,
  0.468750;0.089050;,
  0.471030;0.085700;,
  0.470070;0.094180;,
  0.467310;0.083140;,
  0.466230;0.091500;,
  0.476300;0.089590;,
  0.478820;0.086960;,
  0.477500;0.094960;,
  0.474990;0.083730;,
  0.473660;0.091500;,
  0.483740;0.107860;,
  0.484100;0.113830;,
  0.481100;0.107860;,
  0.486740;0.107320;,
  0.483860;0.101470;,
  0.476540;0.123560;,
  0.473660;0.122600;,
  0.477260;0.118070;,
  0.476060;0.129470;,
  0.479660;0.124870;,
  0.476540;0.107080;,
  0.477020;0.112570;,
  0.473430;0.106840;,
  0.479180;0.106420;,
  0.475940;0.100390;,
  0.468150;0.122720;,
  0.469110;0.128400;,
  0.464910;0.125050;,
  0.470670;0.120810;,
  0.466590;0.117590;,
  0.468150;0.105530;,
  0.468750;0.110840;,
  0.465030;0.108040;,
  0.470070;0.102960;,
  0.466230;0.100030;,
  0.468870;0.197060;,
  0.476420;0.189420;,
  0.480140;0.198850;,
  0.446440;0.204820;,
  0.443200;0.196220;,
  0.446320;0.196940;,
  0.437090;0.203510;,
  0.432650;0.240170;,
  0.423290;0.231210;,
  0.430250;0.200880;,
  0.444040;0.196460;,
  0.445600;0.249000;,
  0.457110;0.204700;,
  0.459990;0.249840;,
  0.469110;0.243030;,
  0.464070;0.203980;,
  0.477740;0.234670;,
  0.459270;0.196220;,
  0.451120;0.196580;,
  0.463710;0.196580;,
  0.458310;0.196340;,
  0.464550;0.197060;,
  0.470670;0.196820;,
  0.470550;0.202670;,
  0.479420;0.199570;,
  0.489380;0.224520;,
  0.496090;0.036710;,
  0.499690;0.031190;,
  0.499210;0.040800;,
  0.495610;0.027340;,
  0.499690;0.021400;,
  0.503530;0.028040;,
  0.502810;0.038360;;
 }
}
