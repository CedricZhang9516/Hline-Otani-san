const string line1 = "#BLTrakFile";
const string line2 = "#x y z Px Py Pz t PDGid EvNum TrkId Parent weight";
const string line3 = "#mm mm mm MeV/c MeV/c MeV/c ns - - - - -";

//const double sigma_x = 20;
const double sigma_x = 2;
//const double sigma_y = 40;
const double sigma_y = 4;
const double sigma_xp= 0.25;
const double sigma_yp= 0.25;
const double pmax = 29.8;
TRandom* rando;

double x, y, z, Px, Py, Pz, p;

//const int    nevt = 100000 + 3;
const int    nevt = 2000000;
//const int    nevt = 2000;
//const int    nevt = 200000;

void macro_generate_beam_single(int seed = 005){
  rando = new TRandom();
  //ofstream wf("g4input.dat");
  //ofstream wf(Form("g4input_150315_1e6_%02d.dat",seed));
  //ofstream wf(Form("g4input_200528_1e6_%02d.dat",seed));
  //ofstream wf(Form("~/g-2/Hline/Otani-san/g4input/g4input_200601_2e6_%03d.dat",seed));
  ofstream wf(Form("g4input_200605_2e6_%03d.dat",seed));
  //ofstream wf(Form("g4input_200601_2e6_%02d.dat",seed));
  wf << line1 << endl;
  wf << line2 << endl;
  wf << line3 << endl;
  rando->SetSeed(seed);
  for(int i=0; i<nevt; i++){
    double t = rando -> Uniform(0,1);
    p = pow(t, 1.0/3.6)*pmax;
    double tx = rando -> Uniform(-1.0*sigma_xp, 1.0*sigma_xp);

    double ty = rando -> Uniform(-1.0*sigma_yp, 1.0*sigma_yp);
    Pz = p/sqrt(tx*tx+ty*ty+1);
    Px = Pz*tx;
    Py = Pz*ty;
    x  = rando -> Gaus(0, sigma_x);
    y  = rando -> Gaus(0, sigma_y);
    z  = 0;
    wf << x  << "\t"
       << y  << "\t"
       << z  << "\t"
       << Px << "\t"
       << Py << "\t"
       << Pz << "\t"
       << "0\t-13\t"<<i << "\t1\t1\t1" << endl;

  }//i
  wf.close();
}


void macro_generate_beam(int start, int stop){

  //for(int i = 007;  i<12; i++){
  for(int i = start;  i<=stop; i++){
    macro_generate_beam_single(i);
    gROOT->ProcessLine( Form(".!mv g4input_200605_2e6_%03d.dat ~/g-2/Hline/Otani-san/g4input/g4input_200605_2e6_%03d.dat",i,i) );
  }





}