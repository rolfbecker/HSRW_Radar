
extern const int16_t sine[1000];

IntervalTimer myTimer;

//storage variables
volatile boolean sendChunk = false;
volatile boolean state = false;
volatile uint16_t buf[1024];
volatile uint16_t idx = 0;
volatile uint16_t count1 = 0;
volatile uint16_t count2 = 0;
volatile uint16_t count3 = 0;
volatile uint32_t val = 0;
volatile uint8_t chunk = 0;

void setup(){
  cli();//stop interrupts
  myTimer.begin(dataproducer, 10);  // 20 us -> 50 KHz, 10 us -> 100 KHz 5 us -> 200 KHz
  Serial.begin(115200);
  pinMode(13,OUTPUT);
  pinMode(12,OUTPUT);
  digitalWrite(13,HIGH);
  digitalWrite(12,HIGH);
  sei();//allow interrupts
}//end setup


void loop() {
  // put your main code here, to run repeatedly:
  if (sendChunk)
  {
    sendChunk = false;
    if (idx > 511) 
    {
      digitalWrite(13,LOW);
      Serial.write((byte *) &buf[0], 1024);
    }
    else 
    {
      digitalWrite(13,HIGH);
      Serial.write((byte *) &buf[512], 1024);
    }
  }
}


void dataproducer()
{
  state = digitalRead(12);
  digitalWrite(12,!state);

  val = ((sine[count1] + 32768)+(sine[count2] + 32768)+(sine[count3] + 32768))/3;
  
  buf[idx] = val & 0x0000FFFF;

  count1 +=1; if (count1>999) count1 = 0;
  count2 +=3; if (count2>999) count2 = 0;
  count3 +=7; if (count3>999) count3 = 0;


  idx++; idx = idx & 1023;

  //buf[idx++] = analogRead(A0);
  if ((idx == 0) || (idx == 512)) sendChunk = true;
}


const int16_t sine[1000] = 
{     0,    206,    412,    618,    823,   1029,   1235,   1441,   1646,
   1852,   2057,   2263,   2468,   2673,   2879,   3084,   3289,   3493,
   3698,   3902,   4107,   4311,   4515,   4719,   4922,   5126,   5329,
   5532,   5735,   5938,   6140,   6342,   6544,   6746,   6947,   7148,
   7349,   7549,   7749,   7949,   8149,   8348,   8547,   8746,   8944,
   9142,   9339,   9536,   9733,   9930,  10126,  10321,  10516,  10711,
  10905,  11099,  11293,  11486,  11679,  11871,  12062,  12254,  12444,
  12634,  12824,  13013,  13202,  13390,  13578,  13765,  13952,  14138,
  14323,  14508,  14692,  14876,  15059,  15242,  15424,  15605,  15786,
  15966,  16145,  16324,  16502,  16680,  16857,  17033,  17208,  17383,
  17557,  17731,  17904,  18076,  18247,  18418,  18588,  18757,  18925,
  19093,  19260,  19426,  19592,  19756,  19920,  20083,  20245,  20407,
  20568,  20727,  20886,  21045,  21202,  21359,  21514,  21669,  21823,
  21976,  22129,  22280,  22431,  22580,  22729,  22877,  23024,  23170,
  23315,  23459,  23602,  23745,  23886,  24027,  24166,  24305,  24442,
  24579,  24715,  24849,  24983,  25116,  25247,  25378,  25508,  25637,
  25764,  25891,  26017,  26141,  26265,  26388,  26509,  26630,  26749,
  26867,  26985,  27101,  27216,  27330,  27443,  27555,  27666,  27776,
  27885,  27992,  28099,  28204,  28308,  28411,  28513,  28614,  28714,
  28813,  28910,  29006,  29102,  29196,  29289,  29380,  29471,  29560,
  29648,  29736,  29821,  29906,  29990,  30072,  30153,  30233,  30312,
  30390,  30466,  30541,  30615,  30688,  30759,  30830,  30899,  30967,
  31034,  31099,  31163,  31226,  31288,  31349,  31408,  31466,  31523,
  31578,  31633,  31686,  31738,  31788,  31837,  31886,  31932,  31978,
  32022,  32065,  32107,  32147,  32187,  32225,  32261,  32297,  32331,
  32364,  32395,  32425,  32454,  32482,  32509,  32534,  32558,  32580,
  32602,  32622,  32640,  32658,  32674,  32689,  32702,  32715,  32726,
  32735,  32744,  32751,  32757,  32761,  32764,  32766,  32767,  32766,
  32764,  32761,  32757,  32751,  32744,  32735,  32726,  32715,  32702,
  32689,  32674,  32658,  32640,  32622,  32602,  32580,  32558,  32534,
  32509,  32482,  32454,  32425,  32395,  32364,  32331,  32297,  32261,
  32225,  32187,  32147,  32107,  32065,  32022,  31978,  31932,  31886,
  31837,  31788,  31738,  31686,  31633,  31578,  31523,  31466,  31408,
  31349,  31288,  31226,  31163,  31099,  31034,  30967,  30899,  30830,
  30759,  30688,  30615,  30541,  30466,  30390,  30312,  30233,  30153,
  30072,  29990,  29906,  29821,  29736,  29648,  29560,  29471,  29380,
  29289,  29196,  29102,  29006,  28910,  28813,  28714,  28614,  28513,
  28411,  28308,  28204,  28099,  27992,  27885,  27776,  27666,  27555,
  27443,  27330,  27216,  27101,  26985,  26867,  26749,  26630,  26509,
  26388,  26265,  26141,  26017,  25891,  25764,  25637,  25508,  25378,
  25247,  25116,  24983,  24849,  24715,  24579,  24442,  24305,  24166,
  24027,  23886,  23745,  23602,  23459,  23315,  23170,  23024,  22877,
  22729,  22580,  22431,  22280,  22129,  21976,  21823,  21669,  21514,
  21359,  21202,  21045,  20886,  20727,  20568,  20407,  20245,  20083,
  19920,  19756,  19592,  19426,  19260,  19093,  18925,  18757,  18588,
  18418,  18247,  18076,  17904,  17731,  17557,  17383,  17208,  17033,
  16857,  16680,  16502,  16324,  16145,  15966,  15786,  15605,  15424,
  15242,  15059,  14876,  14692,  14508,  14323,  14138,  13952,  13765,
  13578,  13390,  13202,  13013,  12824,  12634,  12444,  12254,  12062,
  11871,  11679,  11486,  11293,  11099,  10905,  10711,  10516,  10321,
  10126,   9930,   9733,   9536,   9339,   9142,   8944,   8746,   8547,
   8348,   8149,   7949,   7749,   7549,   7349,   7148,   6947,   6746,
   6544,   6342,   6140,   5938,   5735,   5532,   5329,   5126,   4922,
   4719,   4515,   4311,   4107,   3902,   3698,   3493,   3289,   3084,
   2879,   2673,   2468,   2263,   2057,   1852,   1646,   1441,   1235,
   1029,    823,    618,    412,    206,      0,   -206,   -412,   -618,
   -823,  -1029,  -1235,  -1441,  -1646,  -1852,  -2057,  -2263,  -2468,
  -2673,  -2879,  -3084,  -3289,  -3493,  -3698,  -3902,  -4107,  -4311,
  -4515,  -4719,  -4922,  -5126,  -5329,  -5532,  -5735,  -5938,  -6140,
  -6342,  -6544,  -6746,  -6947,  -7148,  -7349,  -7549,  -7749,  -7949,
  -8149,  -8348,  -8547,  -8746,  -8944,  -9142,  -9339,  -9536,  -9733,
  -9930, -10126, -10321, -10516, -10711, -10905, -11099, -11293, -11486,
 -11679, -11871, -12062, -12254, -12444, -12634, -12824, -13013, -13202,
 -13390, -13578, -13765, -13952, -14138, -14323, -14508, -14692, -14876,
 -15059, -15242, -15424, -15605, -15786, -15966, -16145, -16324, -16502,
 -16680, -16857, -17033, -17208, -17383, -17557, -17731, -17904, -18076,
 -18247, -18418, -18588, -18757, -18925, -19093, -19260, -19426, -19592,
 -19756, -19920, -20083, -20245, -20407, -20568, -20727, -20886, -21045,
 -21202, -21359, -21514, -21669, -21823, -21976, -22129, -22280, -22431,
 -22580, -22729, -22877, -23024, -23170, -23315, -23459, -23602, -23745,
 -23886, -24027, -24166, -24305, -24442, -24579, -24715, -24849, -24983,
 -25116, -25247, -25378, -25508, -25637, -25764, -25891, -26017, -26141,
 -26265, -26388, -26509, -26630, -26749, -26867, -26985, -27101, -27216,
 -27330, -27443, -27555, -27666, -27776, -27885, -27992, -28099, -28204,
 -28308, -28411, -28513, -28614, -28714, -28813, -28910, -29006, -29102,
 -29196, -29289, -29380, -29471, -29560, -29648, -29736, -29821, -29906,
 -29990, -30072, -30153, -30233, -30312, -30390, -30466, -30541, -30615,
 -30688, -30759, -30830, -30899, -30967, -31034, -31099, -31163, -31226,
 -31288, -31349, -31408, -31466, -31523, -31578, -31633, -31686, -31738,
 -31788, -31837, -31886, -31932, -31978, -32022, -32065, -32107, -32147,
 -32187, -32225, -32261, -32297, -32331, -32364, -32395, -32425, -32454,
 -32482, -32509, -32534, -32558, -32580, -32602, -32622, -32640, -32658,
 -32674, -32689, -32702, -32715, -32726, -32735, -32744, -32751, -32757,
 -32761, -32764, -32766, -32767, -32766, -32764, -32761, -32757, -32751,
 -32744, -32735, -32726, -32715, -32702, -32689, -32674, -32658, -32640,
 -32622, -32602, -32580, -32558, -32534, -32509, -32482, -32454, -32425,
 -32395, -32364, -32331, -32297, -32261, -32225, -32187, -32147, -32107,
 -32065, -32022, -31978, -31932, -31886, -31837, -31788, -31738, -31686,
 -31633, -31578, -31523, -31466, -31408, -31349, -31288, -31226, -31163,
 -31099, -31034, -30967, -30899, -30830, -30759, -30688, -30615, -30541,
 -30466, -30390, -30312, -30233, -30153, -30072, -29990, -29906, -29821,
 -29736, -29648, -29560, -29471, -29380, -29289, -29196, -29102, -29006,
 -28910, -28813, -28714, -28614, -28513, -28411, -28308, -28204, -28099,
 -27992, -27885, -27776, -27666, -27555, -27443, -27330, -27216, -27101,
 -26985, -26867, -26749, -26630, -26509, -26388, -26265, -26141, -26017,
 -25891, -25764, -25637, -25508, -25378, -25247, -25116, -24983, -24849,
 -24715, -24579, -24442, -24305, -24166, -24027, -23886, -23745, -23602,
 -23459, -23315, -23170, -23024, -22877, -22729, -22580, -22431, -22280,
 -22129, -21976, -21823, -21669, -21514, -21359, -21202, -21045, -20886,
 -20727, -20568, -20407, -20245, -20083, -19920, -19756, -19592, -19426,
 -19260, -19093, -18925, -18757, -18588, -18418, -18247, -18076, -17904,
 -17731, -17557, -17383, -17208, -17033, -16857, -16680, -16502, -16324,
 -16145, -15966, -15786, -15605, -15424, -15242, -15059, -14876, -14692,
 -14508, -14323, -14138, -13952, -13765, -13578, -13390, -13202, -13013,
 -12824, -12634, -12444, -12254, -12062, -11871, -11679, -11486, -11293,
 -11099, -10905, -10711, -10516, -10321, -10126,  -9930,  -9733,  -9536,
  -9339,  -9142,  -8944,  -8746,  -8547,  -8348,  -8149,  -7949,  -7749,
  -7549,  -7349,  -7148,  -6947,  -6746,  -6544,  -6342,  -6140,  -5938,
  -5735,  -5532,  -5329,  -5126,  -4922,  -4719,  -4515,  -4311,  -4107,
  -3902,  -3698,  -3493,  -3289,  -3084,  -2879,  -2673,  -2468,  -2263,
  -2057,  -1852,  -1646,  -1441,  -1235,  -1029,   -823,   -618,   -412,
   -206};

