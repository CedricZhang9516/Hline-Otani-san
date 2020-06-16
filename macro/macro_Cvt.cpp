//#include "/Users/zhangce/WorkArea/CZhang/CZhang.cxx"
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

double light = 299792458; // m/s
double massMu = 106.16; // MeV/c2


void macro_Cvt_single(TString name1 = "", TString name2 = ""){


  cout<<name1.Data()<<endl;
  Float_t rX,rY,rZ,rPx,rPy,rPz,rEk,rT;
  Float_t PDGid, EventID, TrackID, ParentID;

  //TFile*   fF2  = new TFile(Form("../Run191215/Mydata/%s",name1.Data()));
  TFile*   fF2  = new TFile(Form("%s",name1.Data()));

  //TTree* fT2  = (TTree*)fF2->Get("VirtualDetector/focus04_det");
  //TTree* fT2  = (TTree*)fF2->Get("VirtualDetector/focus04_det");
  TTree* fT2  = (TTree*)fF2->Get("VirtualDetector/focus_det_5");


  fT2->SetBranchAddress("x",&rX);
  fT2->SetBranchAddress("y",&rY);
  fT2->SetBranchAddress("z",&rZ);
  fT2->SetBranchAddress("Px",&rPx);
  fT2->SetBranchAddress("Py",&rPy);
  fT2->SetBranchAddress("Pz",&rPz);
  //fT2->SetBranchAddress("rEk",&rEk);
  fT2->SetBranchAddress("t",&rT);
  //fT2->Draw("Px/Pz:(x-100)");
  //fT2->Draw("Py/Pz:(y-100)");

  fT2->SetBranchAddress("PDGid", &PDGid);
  fT2->SetBranchAddress("EventID", &EventID);
  fT2->SetBranchAddress("TrackID", &TrackID);
  fT2->SetBranchAddress("ParentID", &ParentID);

  int N = fT2->GetEntries();

  ofstream outFile;
  outFile.open(Form("%s_%i.txt",name2.Data(),N));




  for (int i = 0; i < N; i++){
    fT2->GetEntry(i);

    double P = sqrt(rPx*rPx + rPy*rPy + rPz*rPz);
    rPx /= P;
    rPy /= P;
    rPz /= P;

    rEk = sqrt(massMu*massMu + P*P ) - massMu;

    //outFile<< rX-100<<" "<<rY<<" "<<-163<<" "<<rPx<<" "<<rPy<<" "<<rPz<<" "<<rEk<<" "<<rT<<endl;
    //outFile<< rX <<" "<<rY<<" "<<-12<<" "<<rPx<<" "<<rPy<<" "<<rPz<<" "<<rEk<<" "<<rT<<endl;

    //if(rEk>0.1)
    outFile<< rX <<" "<<rY<<" "<<-12<<" "<<rPx<<" "<<rPy<<" "<<rPz<<" "<<rEk<<" "<<0<<endl;
    // 200526 only for checking the absolute momentum btw Yamazaki-san and GM
    //if(rEk>0.1)outFile<< rX <<" "<<rY<<" "<<-12<<" "<<P*rPx<<" "<<P*rPy<<" "<<P*rPz<<" "<<rEk<<" "<<0<<endl;

  }

  outFile.close();
  cout<<"done"<<endl;
  ///home/had/zhangce/1S2SMuSim/SimBeamStop/build/Application_Main 19 run0221.mac 475 SimBeamStop_200601_1e6_000_164994.root /home/had/zhangce/g-2/Hline/Otani-san/data/g4output_200601_1e6_000_focus05.txt 164994

}

void macro_Cvt(TString name, int Nrun){

  //TString name = "S2area_191202_tot_NSL";
  //TString name = "/home/had/zhangce/Hline/data/g-2_output/g4beamline_TDR_Fig.3.14.BLTrackFile";
  //TString name = "/home/had/zhangce/Hline/data/g-2_output/g4beamline_SurfaceMuon.BLTrackFile";
  //TString name = "/home/had/zhangce/g-2/Hline/Otani-san/data/g4output_200603_2e6_0";



  TString name2;

  for(int i = Nrun; i<=Nrun; i++){
    stringstream ss; ss << setw(3) << setfill('0') << i ;
    //stringstream ss; ss << Nrun;
    //cout<<ss.str()<<" "<<Nrun<<" "<<i<<endl;
    cout<<"Cvting Run "<<ss.str()<<endl;
    /////// CHANGE THE  NAME1 AND NAME2 DUE to the single/multi-file

    TString name1 = name.Data() + ss.str() + ".root";
    //TString name1 = name + ".root";

    name2 = name.Data() + ss.str() + "_focus05";
    //name2 = name + "ABS_P_focus04_" + ss.str();
    //name2 = name + "ABS_P_focus05_" + ss.str();
    //name2 = name;

    macro_Cvt_single(name1 , name2);
  }

}
