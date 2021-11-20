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
 -22.66681;-4.62353;1.08831;,
 -30.47992;-11.44209;0.29086;,
 -31.08921;-10.30418;0.66717;,
 -24.09145;-3.83504;1.12416;,
 -25.90136;-12.06033;11.41917;,
 -21.46617;-5.49266;11.17725;,
 -19.91609;-6.02130;9.73469;,
 -22.66681;-4.62353;1.08831;,
 -31.26840;-15.73393;8.62365;,
 -29.25241;-22.99156;11.38331;,
 -22.89081;-16.17297;14.70750;,
 -16.06331;-8.38673;15.55871;,
 -15.68699;-8.38673;14.00862;,
 -30.47992;-11.44209;0.29086;,
 -30.47992;-16.69266;7.10940;,
 -29.07320;-22.99156;10.20060;,
 -21.57369;-25.35699;9.20603;,
 -17.87322;-19.58674;12.13595;,
 -11.79835;-14.15696;12.87967;,
 -12.12090;-13.27888;11.77754;,
 -22.16505;-25.09715;8.31005;,
 -16.36794;-25.79603;3.07742;,
 -9.21787;-17.83059;4.71709;,
 -10.08698;-16.52241;4.24220;,
 -17.48794;-25.09715;2.45022;,
 -17.48794;-25.09715;2.45022;,
 -10.08698;-16.52241;4.24220;,
 -18.23162;-17.31090;-3.42755;,
 -16.74426;-20.80530;1.75135;,
 -18.66170;-23.60979;0.45215;,
 -20.57017;-19.49714;-4.79840;,
 -22.84601;-12.92945;-4.85216;,
 -25.48919;-15.11568;-6.13346;,
 -26.45688;-10.83280;-1.48324;,
 -29.29720;-12.84880;-2.68387;,
 -27.21848;-13.36849;6.02524;,
 -29.64665;-15.90418;5.26366;,
 -24.45881;-17.74098;9.70779;,
 -26.84215;-20.28562;8.91934;,
 -22.01273;-23.60979;6.52700;,
 -19.84442;-20.80530;7.53052;,
 -16.74426;-20.80530;1.75135;,
 -18.66170;-23.60979;0.45215;,
 -30.47992;-8.64657;5.46077;,
 -29.69143;-9.51568;5.49663;,
 -25.79384;-5.14323;7.17212;,
 -32.13753;-10.74321;-1.26819;,
 -32.44217;-9.87409;-1.65349;,
 -26.38520;-12.92945;-5.94530;,
 -26.84215;-12.58001;-6.77856;,
 -20.76729;-16.08337;-7.83584;,
 -20.91961;-16.08337;-6.80547;,
 -26.67191;-4.35472;7.01981;,
 -23.16857;-1.12015;0.22814;,
 -20.11321;-7.06962;-6.46497;,
 -17.12954;-12.92945;-8.24802;,
 -17.85531;-21.94321;-4.47588;,
 -18.20474;-21.24434;-3.83972;,
 -22.38009;-1.72944;0.47006;,
 -19.87129;-7.76850;-5.42564;,
 -17.04890;-12.66962;-7.22659;,
 -12.90938;-15.82353;-4.59236;,
 -15.71386;-26.75475;2.03805;,
 -16.47546;-25.61682;2.06495;,
 -15.92890;-23.95923;7.83516;,
 -15.16730;-24.91795;8.06813;,
 -13.89498;-21.07409;9.77051;,
 -13.57242;-15.29489;-3.91140;,
 -8.00827;-17.04209;2.71006;,
 -9.41498;-18.96850;9.46587;,
 -12.89147;-21.85363;10.05725;,
 -10.32890;-18.09937;9.21499;,
 -9.41498;-16.69266;2.78174;,
 -17.39834;-19.05810;-0.30053;,
 -23.28505;-24.91795;-2.81826;,
 -27.55000;-18.79826;-6.12450;,
 -22.66681;-13.01905;-4.75363;,
 -19.34266;-9.43505;-6.22305;,
 -15.95578;-12.92945;-6.03489;,
 -12.45242;-16.78226;-0.42596;,
 -4.71098;-9.95474;0.02203;,
 -6.41338;-2.60751;-8.07777;,
 -3.01754;-11.01200;-0.78438;,
 -30.56952;-16.69266;-3.05123;,
 -25.55192;-10.57296;-1.17860;,
 -22.84601;-6.63056;-0.82019;,
 -8.67130;3.78096;-9.26944;,
 -26.38520;-13.10865;6.46428;,
 -23.71513;-9.08562;8.12189;,
 -8.93114;7.45455;12.14491;,
 -11.26971;9.99024;-1.82371;,
 -5.47259;5.17872;-10.70306;,
 -4.53178;-3.04657;-10.15653;,
 -31.26840;-18.18002;2.42333;,
 -30.39032;-20.63505;5.29947;,
 -21.75289;-18.35921;8.91934;,
 -18.03450;-14.15696;10.79197;,
 -5.08730;-3.91568;14.26846;,
 -2.15739;-2.51791;14.09821;,
 -3.96730;9.90064;11.97470;,
 -6.35066;12.26609;-1.67140;,
 -26.77943;-25.00755;5.59517;,
 -17.39834;-19.05810;-0.30053;,
 -13.85018;-17.04209;6.89437;,
 -4.26298;-10.83280;9.30461;,
 -2.82939;-10.92242;9.31356;,
 -0.35642;-14.59602;8.41754;,
 2.13445;-2.34768;13.76670;,
 -23.28505;-24.91795;-2.81826;,
 1.25637;11.03858;11.19515;,
 -0.44602;13.84304;-1.24132;,
 -1.49434;4.73968;-11.50946;,
 -1.38682;-4.88338;-11.79619;,
 -0.89403;-15.47409;-2.22693;,
 -12.45242;-16.78226;-0.42596;,
 -4.71098;-9.95474;0.02203;,
 -3.01754;-11.01200;-0.78438;,
 -0.89403;-15.47409;-2.22693;;
 
 165;
 3;0,1,2;,
 3;2,3,0;,
 3;3,2,4;,
 3;5,3,4;,
 3;3,5,6;,
 3;6,7,3;,
 3;8,4,2;,
 3;4,8,9;,
 3;9,10,4;,
 3;5,4,10;,
 3;10,11,5;,
 3;5,11,12;,
 3;12,6,5;,
 3;8,2,13;,
 3;13,14,8;,
 3;9,8,14;,
 3;14,15,9;,
 3;16,9,15;,
 3;10,9,16;,
 3;16,17,10;,
 3;11,10,17;,
 3;17,18,11;,
 3;11,18,19;,
 3;19,12,11;,
 3;15,20,16;,
 3;21,16,20;,
 3;16,21,17;,
 3;17,21,22;,
 3;18,17,22;,
 3;18,22,23;,
 3;23,19,18;,
 3;20,24,21;,
 3;22,21,25;,
 3;25,26,22;,
 3;27,28,29;,
 3;29,30,27;,
 3;31,27,30;,
 3;30,32,31;,
 3;33,31,32;,
 3;32,34,33;,
 3;35,33,34;,
 3;34,36,35;,
 3;37,35,36;,
 3;36,38,37;,
 3;37,38,39;,
 3;39,40,37;,
 3;41,40,39;,
 3;39,42,41;,
 3;43,44,45;,
 3;46,44,43;,
 3;43,47,46;,
 3;48,46,47;,
 3;47,49,48;,
 3;48,49,50;,
 3;50,51,48;,
 3;45,52,43;,
 3;43,52,53;,
 3;53,47,43;,
 3;49,47,53;,
 3;53,54,49;,
 3;50,49,54;,
 3;54,55,50;,
 3;56,50,55;,
 3;50,56,57;,
 3;57,51,50;,
 3;53,52,45;,
 3;45,58,53;,
 3;54,53,58;,
 3;58,59,54;,
 3;54,59,60;,
 3;60,55,54;,
 3;61,55,60;,
 3;55,61,56;,
 3;62,56,61;,
 3;57,56,62;,
 3;62,63,57;,
 3;64,63,62;,
 3;62,65,64;,
 3;66,64,65;,
 3;60,67,61;,
 3;68,61,67;,
 3;61,68,62;,
 3;62,68,69;,
 3;69,65,62;,
 3;70,65,69;,
 3;65,70,66;,
 3;66,70,69;,
 3;69,71,66;,
 3;71,69,68;,
 3;68,72,71;,
 3;67,72,68;,
 3;73,74,75;,
 3;75,76,73;,
 3;73,76,77;,
 3;77,78,73;,
 3;78,79,73;,
 3;80,79,78;,
 3;78,81,80;,
 3;82,80,81;,
 3;76,75,83;,
 3;83,84,76;,
 3;76,84,85;,
 3;85,77,76;,
 3;86,77,85;,
 3;77,86,81;,
 3;81,78,77;,
 3;87,84,83;,
 3;84,87,88;,
 3;88,85,84;,
 3;85,88,89;,
 3;89,90,85;,
 3;85,90,86;,
 3;91,86,90;,
 3;81,86,91;,
 3;91,92,81;,
 3;81,92,82;,
 3;83,93,87;,
 3;94,87,93;,
 3;95,87,94;,
 3;88,87,95;,
 3;95,96,88;,
 3;89,88,96;,
 3;96,97,89;,
 3;89,97,98;,
 3;98,99,89;,
 3;90,89,99;,
 3;99,100,90;,
 3;90,100,91;,
 3;94,101,95;,
 3;102,95,101;,
 3;102,103,95;,
 3;95,103,96;,
 3;96,103,104;,
 3;104,97,96;,
 3;98,97,104;,
 3;104,105,98;,
 3;98,105,106;,
 3;106,107,98;,
 3;99,98,107;,
 3;101,108,102;,
 3;107,109,99;,
 3;100,99,109;,
 3;109,110,100;,
 3;100,110,111;,
 3;111,91,100;,
 3;91,111,112;,
 3;112,92,91;,
 3;82,92,112;,
 3;112,113,82;,
 3;103,102,114;,
 3;103,114,115;,
 3;115,104,103;,
 3;105,104,115;,
 3;115,116,105;,
 3;106,105,116;,
 3;116,117,106;,
 3;110,109,111;,
 3;111,109,107;,
 3;107,106,111;,
 3;106,112,111;,
 3;106,113,112;,
 3;93,83,75;,
 3;75,108,93;,
 3;108,94,93;,
 3;108,101,94;;
 
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
    "C:\\Users\\student\\Desktop\\C++Game\\3dPersonalProject000\\3dPersonalProject000\\data\\TEXTURE\\Enemy\\chosen.png";
   }
  }
 }
 MeshNormals {
  172;
  -0.057067;0.157696;-0.985837;,
  -0.122044;0.252117;-0.959970;,
  0.008699;0.061097;-0.998094;,
  -0.643831;0.441213;0.625150;,
  -0.601117;0.423257;0.677872;,
  0.420374;0.906034;0.048870;,
  -0.628460;0.419905;0.654765;,
  -0.392664;-0.058637;0.917811;,
  -0.210195;-0.091489;0.973369;,
  -0.024151;-0.111968;0.993418;,
  0.570648;0.809195;0.139876;,
  -0.921117;-0.322297;-0.218328;,
  -0.579678;-0.809056;-0.096960;,
  -0.282286;-0.955841;-0.081751;,
  0.388841;-0.540438;0.746143;,
  0.382047;-0.531032;0.756336;,
  0.859571;0.488608;0.149670;,
  -0.308041;-0.936443;-0.167885;,
  -0.306640;-0.927015;-0.215905;,
  0.564222;-0.654446;0.503343;,
  0.872043;0.487858;0.039176;,
  -0.377582;-0.875561;-0.301372;,
  0.688479;-0.217673;-0.691820;,
  0.795645;-0.597711;0.098445;,
  0.821169;-0.513860;-0.248253;,
  0.521274;-0.054508;-0.851647;,
  0.190741;0.342707;-0.919875;,
  -0.032557;0.546958;-0.836527;,
  -0.398874;0.804163;-0.440706;,
  -0.594003;0.797493;-0.105668;,
  -0.678703;0.603167;0.418989;,
  -0.653598;0.432615;0.621010;,
  -0.559770;0.293725;0.774844;,
  -0.562670;0.286762;0.775352;,
  0.444800;-0.578098;0.684072;,
  0.440211;-0.584305;0.681764;,
  -0.605149;-0.311272;0.732738;,
  -0.514779;-0.436583;0.737833;,
  -0.246514;-0.138798;0.959149;,
  -0.868746;-0.494372;0.029599;,
  -0.795337;-0.589119;-0.142753;,
  -0.564270;-0.797350;-0.214085;,
  -0.503227;-0.859995;-0.084686;,
  -0.715299;-0.694961;-0.073330;,
  -0.697651;-0.708976;-0.103135;,
  -0.266252;-0.111555;0.957426;,
  -0.612976;0.689113;-0.386501;,
  -0.264266;0.306873;-0.914326;,
  0.157602;-0.218920;-0.962931;,
  0.446526;-0.437677;-0.780419;,
  -0.869853;-0.487030;-0.078466;,
  0.735372;0.670251;0.099959;,
  0.907422;0.414736;0.067667;,
  0.774379;0.627000;-0.084905;,
  0.598922;0.787403;-0.145906;,
  0.737848;-0.622045;-0.261995;,
  -0.830143;-0.556437;0.035239;,
  -0.749621;-0.467946;0.468076;,
  -0.619666;-0.360796;0.697023;,
  -0.277729;0.017005;0.960509;,
  0.457232;0.887856;-0.051485;,
  0.409555;0.905173;0.113696;,
  0.712828;-0.682235;0.162577;,
  0.633744;-0.693332;0.343015;,
  -0.043983;0.234098;0.971218;,
  0.245498;0.958279;0.146394;,
  0.205547;-0.451696;-0.868171;,
  0.491449;-0.123278;-0.862137;,
  0.487631;-0.164887;-0.857338;,
  0.327118;-0.359150;-0.874074;,
  -0.121424;-0.354233;-0.927240;,
  0.162945;-0.550370;-0.818866;,
  0.517045;-0.790431;-0.328455;,
  0.479865;-0.818956;-0.314707;,
  -0.248929;-0.376978;-0.892144;,
  -0.751117;-0.618454;-0.230949;,
  -0.661735;0.659002;-0.357524;,
  -0.757790;0.598105;-0.260815;,
  -0.773133;0.534086;-0.342078;,
  -0.492940;0.203273;-0.845985;,
  -0.768745;0.410856;0.490130;,
  -0.810114;0.579756;0.087169;,
  -0.672630;0.713920;0.194648;,
  -0.600372;0.768854;-0.220039;,
  -0.432183;0.258359;-0.863984;,
  -0.661922;-0.403590;-0.631644;,
  -0.796622;0.515417;0.315815;,
  -0.539029;0.070176;0.839359;,
  -0.296222;-0.167470;0.940323;,
  -0.067065;-0.307456;0.949196;,
  0.050255;-0.230511;0.971771;,
  -0.001436;-0.210217;0.977654;,
  0.042120;0.178351;0.983065;,
  -0.256147;0.940343;-0.223928;,
  -0.330182;-0.210442;0.920160;,
  0.428882;-0.849630;0.306901;,
  0.181481;-0.561226;0.807521;,
  -0.513021;-0.690686;0.509668;,
  -0.138370;-0.438330;0.888099;,
  0.089883;-0.014390;0.995848;,
  0.103281;0.194175;0.975515;,
  -0.236033;0.945252;-0.225361;,
  -0.140196;0.564394;-0.813513;,
  -0.619648;-0.296653;-0.726659;,
  -0.910915;-0.395420;-0.117804;,
  -0.714313;0.602591;0.355866;,
  -0.642084;0.644543;0.415081;,
  0.427616;0.903690;0.022095;,
  0.393661;0.915238;0.085851;,
  0.483966;0.874997;-0.012515;,
  0.717014;0.676895;0.166444;,
  -0.897363;-0.354280;-0.263107;,
  -0.881908;-0.379908;-0.279122;,
  -0.894075;-0.358112;-0.269048;,
  -0.796174;-0.582760;-0.162781;,
  0.262751;-0.567646;0.780218;,
  0.859918;0.503099;0.086210;,
  0.572324;-0.628926;0.526210;,
  0.830818;0.556409;0.012235;,
  0.373572;-0.139058;-0.917119;,
  0.397738;-0.171487;-0.901331;,
  0.348701;-0.106367;-0.931179;,
  0.145843;-0.423730;0.893970;,
  0.153363;-0.420691;0.894147;,
  -0.715821;0.698272;0.004179;,
  -0.736081;0.674359;-0.058525;,
  -0.598968;0.712912;-0.364684;,
  -0.313392;0.448271;-0.837161;,
  -0.032805;-0.025534;-0.999135;,
  -0.898645;-0.438516;-0.011864;,
  0.562445;0.770806;0.299190;,
  0.493098;0.658846;0.568133;,
  0.441111;0.694097;0.568902;,
  0.849200;0.518710;-0.098991;,
  0.771155;0.599797;-0.213456;,
  0.591111;-0.470738;-0.654976;,
  -0.843934;-0.531311;0.074054;,
  0.759979;-0.583064;-0.287174;,
  0.666450;-0.702816;0.248785;,
  -0.262569;0.016864;0.964766;,
  -0.053374;0.253312;0.965911;,
  0.432787;0.852564;0.292968;,
  0.600423;0.727319;0.332415;,
  -0.591040;-0.774354;-0.225936;,
  -0.617307;-0.642909;-0.453431;,
  -0.513086;0.475380;-0.714672;,
  -0.403798;0.519774;-0.752850;,
  -0.672829;0.381089;-0.634092;,
  -0.430147;0.015619;0.902624;,
  -0.187084;0.126608;0.974151;,
  -0.342127;0.913655;0.219507;,
  0.489623;-0.845440;0.213309;,
  0.445299;-0.852135;0.274909;,
  0.639484;-0.705423;0.305677;,
  0.626336;-0.737602;0.252283;,
  -0.223818;0.948812;0.222847;,
  0.262730;-0.959310;-0.103423;,
  -0.061567;-0.993942;-0.091048;,
  -0.860396;-0.507034;0.051337;,
  0.991200;0.031011;-0.128689;,
  0.990898;0.035407;-0.129872;,
  0.992700;-0.009814;-0.120209;,
  0.987299;-0.041465;-0.153369;,
  0.995242;-0.036504;-0.090342;,
  0.998839;0.006666;-0.047713;,
  0.998723;0.000832;-0.050510;,
  -0.720171;-0.634923;-0.279691;,
  -0.718810;-0.642206;-0.266241;,
  -0.718252;-0.642952;-0.265945;,
  -0.721743;-0.626942;-0.293310;,
  -0.723480;-0.618314;-0.307025;,
  -0.723508;-0.618253;-0.307082;;
  165;
  3;0,1,0;,
  3;0,2,0;,
  3;105,106,3;,
  3;4,105,3;,
  3;107,108,5;,
  3;5,109,107;,
  3;6,3,106;,
  3;3,6,7;,
  3;7,8,3;,
  3;4,3,8;,
  3;8,9,4;,
  3;108,110,10;,
  3;10,5,108;,
  3;111,112,113;,
  3;113,11,111;,
  3;114,111,11;,
  3;11,12,114;,
  3;13,114,12;,
  3;8,7,115;,
  3;115,14,8;,
  3;9,8,14;,
  3;14,15,9;,
  3;110,116,16;,
  3;16,10,110;,
  3;12,17,13;,
  3;18,13,17;,
  3;115,117,14;,
  3;14,117,19;,
  3;15,14,19;,
  3;116,118,20;,
  3;20,16,116;,
  3;17,21,18;,
  3;119,120,119;,
  3;119,121,119;,
  3;22,23,24;,
  3;24,25,22;,
  3;26,22,25;,
  3;25,27,26;,
  3;28,26,27;,
  3;27,29,28;,
  3;30,28,29;,
  3;29,31,30;,
  3;32,30,31;,
  3;31,33,32;,
  3;122,123,34;,
  3;34,35,122;,
  3;23,35,34;,
  3;34,24,23;,
  3;36,37,38;,
  3;39,37,36;,
  3;36,40,39;,
  3;41,39,40;,
  3;40,42,41;,
  3;41,42,43;,
  3;43,44,41;,
  3;38,45,36;,
  3;124,125,46;,
  3;46,126,124;,
  3;127,126,46;,
  3;46,47,127;,
  3;128,127,47;,
  3;47,48,128;,
  3;49,128,48;,
  3;43,129,50;,
  3;50,44,43;,
  3;130,131,132;,
  3;132,51,130;,
  3;133,130,51;,
  3;51,52,133;,
  3;133,52,53;,
  3;53,134,133;,
  3;54,134,53;,
  3;48,135,49;,
  3;55,49,135;,
  3;50,129,136;,
  3;136,56,50;,
  3;57,56,136;,
  3;136,58,57;,
  3;59,57,58;,
  3;53,60,54;,
  3;61,54,60;,
  3;135,137,55;,
  3;55,137,62;,
  3;62,138,55;,
  3;63,138,62;,
  3;58,139,59;,
  3;59,139,140;,
  3;140,64,59;,
  3;141,142,61;,
  3;61,65,141;,
  3;60,65,61;,
  3;66,67,68;,
  3;68,69,66;,
  3;66,69,70;,
  3;70,71,66;,
  3;71,72,66;,
  3;73,72,71;,
  3;71,74,73;,
  3;75,143,144;,
  3;145,146,76;,
  3;76,77,145;,
  3;145,77,78;,
  3;78,147,145;,
  3;79,147,78;,
  3;70,79,74;,
  3;74,71,70;,
  3;80,77,76;,
  3;77,80,81;,
  3;81,78,77;,
  3;78,81,82;,
  3;82,83,78;,
  3;78,83,79;,
  3;84,79,83;,
  3;74,79,84;,
  3;84,85,74;,
  3;74,85,75;,
  3;76,86,80;,
  3;87,80,86;,
  3;88,80,87;,
  3;148,80,88;,
  3;88,89,148;,
  3;149,148,89;,
  3;89,90,149;,
  3;149,90,91;,
  3;91,92,149;,
  3;83,82,150;,
  3;150,93,83;,
  3;83,93,84;,
  3;87,94,88;,
  3;151,152,153;,
  3;151,95,152;,
  3;88,95,89;,
  3;89,95,96;,
  3;96,90,89;,
  3;91,90,96;,
  3;96,97,91;,
  3;91,97,98;,
  3;98,99,91;,
  3;92,91,99;,
  3;153,154,151;,
  3;99,100,92;,
  3;93,150,155;,
  3;155,101,93;,
  3;93,101,102;,
  3;102,84,93;,
  3;84,102,103;,
  3;103,85,84;,
  3;75,85,103;,
  3;103,104,75;,
  3;95,151,72;,
  3;95,72,73;,
  3;73,156,95;,
  3;157,156,73;,
  3;143,75,97;,
  3;158,97,75;,
  3;75,104,158;,
  3;159,160,161;,
  3;161,160,162;,
  3;162,163,161;,
  3;163,164,161;,
  3;163,165,164;,
  3;166,167,168;,
  3;168,169,166;,
  3;169,170,166;,
  3;169,171,170;;
 }
 MeshTextureCoords {
  118;
  0.325900;0.189060;,
  0.324700;0.156930;,
  0.322720;0.157890;,
  0.323510;0.187980;,
  0.305030;0.169470;,
  0.307490;0.193120;,
  0.307850;0.197300;,
  0.323990;0.193240;,
  0.308060;0.148460;,
  0.296700;0.140220;,
  0.296700;0.168760;,
  0.297180;0.197420;,
  0.297330;0.201600;,
  0.323390;0.153830;,
  0.308750;0.144760;,
  0.296670;0.137110;,
  0.285060;0.147620;,
  0.287520;0.170070;,
  0.286590;0.194550;,
  0.286260;0.198850;,
  0.284640;0.144280;,
  0.272890;0.152990;,
  0.272070;0.188700;,
  0.271620;0.194310;,
  0.272500;0.148460;,
  0.270820;0.152280;,
  0.269460;0.188940;,
  0.507610;0.150960;,
  0.507610;0.131260;,
  0.502330;0.131260;,
  0.502330;0.150960;,
  0.507610;0.172100;,
  0.502330;0.172100;,
  0.507610;0.190610;,
  0.502330;0.190610;,
  0.507610;0.218670;,
  0.502330;0.218670;,
  0.507610;0.238260;,
  0.502330;0.238260;,
  0.502330;0.253900;,
  0.507610;0.253900;,
  0.507610;0.269660;,
  0.502330;0.269660;,
  0.408420;0.161830;,
  0.410100;0.163030;,
  0.410700;0.144520;,
  0.399550;0.178070;,
  0.399060;0.175210;,
  0.384790;0.172580;,
  0.385630;0.169710;,
  0.374480;0.161350;,
  0.374360;0.164700;,
  0.409020;0.145350;,
  0.399550;0.132340;,
  0.385030;0.138070;,
  0.374420;0.143080;,
  0.364160;0.166490;,
  0.364760;0.169120;,
  0.399550;0.129590;,
  0.384310;0.134250;,
  0.374420;0.139860;,
  0.365000;0.141170;,
  0.353310;0.170430;,
  0.353490;0.173530;,
  0.345330;0.166610;,
  0.346470;0.164460;,
  0.342820;0.156100;,
  0.365360;0.137710;,
  0.352470;0.136870;,
  0.344970;0.144400;,
  0.344370;0.155140;,
  0.343650;0.142610;,
  0.352710;0.133170;,
  0.519600;0.430630;,
  0.531110;0.418930;,
  0.525840;0.396480;,
  0.513360;0.402210;,
  0.505450;0.408180;,
  0.507850;0.421560;,
  0.513600;0.439950;,
  0.502090;0.457860;,
  0.487580;0.437320;,
  0.500890;0.463350;,
  0.524160;0.382630;,
  0.511210;0.384540;,
  0.503530;0.386210;,
  0.480260;0.420600;,
  0.512400;0.358510;,
  0.504730;0.357310;,
  0.473790;0.356360;,
  0.475700;0.394330;,
  0.475340;0.426570;,
  0.484460;0.444250;,
  0.524400;0.365430;,
  0.525360;0.353970;,
  0.513840;0.334150;,
  0.504970;0.331760;,
  0.479660;0.322920;,
  0.474620;0.320060;,
  0.466350;0.355880;,
  0.468750;0.395760;,
  0.527760;0.335100;,
  0.516960;0.304770;,
  0.507130;0.312170;,
  0.488540;0.298320;,
  0.486380;0.294020;,
  0.484820;0.278740;,
  0.468390;0.312650;,
  0.530160;0.310260;,
  0.458310;0.354450;,
  0.459750;0.398150;,
  0.471270;0.436130;,
  0.482420;0.455470;,
  0.499690;0.477680;,
  0.509050;0.297130;,
  0.496330;0.284710;,
  0.495610;0.279930;,
  0.493930;0.263450;;
 }
}
