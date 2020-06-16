//const double min_xy  = -300;
const double min_xy  = -100;
//const double max_xy  =  300;
const double max_xy  =  100;
//const double binw_xy =  2.0;
const double binw_xy =  2.0;
//const double binw_xy =  0.1;
const int    nbin_xy = (int)((max_xy-min_xy)/binw_xy);

//const double min_pt  = -0.2;
const double min_pt  = -0.3;
//const double max_pt  =  0.2;
const double max_pt  =  0.3;
const double binw_pt =  0.004;
const int    nbin_pt = (int)((max_pt-min_pt)/binw_pt);

//const double min_pt  = -0.2;
const double min_p  = 5;
//const double max_pt  =  0.2;
const double max_p  =  34;
const double binw_p =  0.2;
const int    nbin_p = (int)((max_pt-min_pt)/binw_pt);


void macro_draw_check(string fname){

  TFile*   fF  = new TFile(fname.c_str(), "read");
  TTree* fT  = (TTree*)fF->Get("VirtualDetector/focus_det_5");
  //TTree* fT  = (TTree*)fF->Get("VirtualDetector/atTarget");
  //TTree* fT  = (TTree*)fF->Get("VirtualDetector/target_det");
  //TTree* fT  = (TTree*)fF->Get("VirtualDetector/focus_det");


  TH1F*    fHx   = new TH1F("fHx",   "x",   nbin_xy, min_xy, max_xy);
  fT -> Project("fHx", "x", "PDGid==-13");
  TH1F*    fHy   = new TH1F("fHy",   "y",   nbin_xy, min_xy, max_xy);
  fT -> Project("fHy", "y", "PDGid==-13");
  TH1F*    fHptx = new TH1F("fHptx", "Px/Pz", nbin_pt, min_pt, max_pt);
  fT -> Project("fHptx", "Px/Pz", "PDGid==-13");
  TH1F*    fHpty = new TH1F("fHpty", "Py/Pz", nbin_pt, min_pt, max_pt);
  fT -> Project("fHpty", "Py/Pz", "PDGid==-13");
  TH2F*    fHxdx = new TH2F("fHxdx", "X vs Px/Pz", (int)(nbin_pt/10), min_pt, max_pt, (int)(nbin_xy/5), min_xy, max_xy);
  fT -> Draw("x:Px/Pz>>fHxdx", "PDGid==-13");
  fHxdx -> GetYaxis() -> SetRangeUser(-50,50);
  fHxdx -> GetXaxis() -> SetRangeUser(-0.4,0.4);
  fHxdx -> GetXaxis() -> SetTitle("Px/Pz");
  fHxdx -> GetYaxis() -> SetTitle("X");
  TH2F*    fHydy = new TH2F("fHydy", "Y vs Py/Pz", (int)(nbin_pt/10), min_pt, max_pt, (int)(nbin_xy/5), min_xy, max_xy);
  fT -> Draw("y:Py/Pz>>fHydy", "PDGid==-13");
  fHydy -> GetYaxis() -> SetRangeUser(-50,50);
  fHydy -> GetXaxis() -> SetRangeUser(-0.4,0.4);
  fHydy -> GetXaxis() -> SetTitle("Py/Pz");
  fHydy -> GetYaxis() -> SetTitle("Y");

  TH1F*    fHp = new TH1F("fHp", "P", nbin_p, min_p, max_p);
  fT -> Project("fHp", "sqrt(Px*Px+Py*Py+Pz*Pz)", "PDGid==-13");

  fHx->SetStats(0);
  fHy->SetStats(0);
  fHptx->SetStats(0);
  fHpty->SetStats(0);
  fHxdx->SetStats(0);
  fHydy->SetStats(0);
  fHp->SetStats(0);

  TH2F*    fHxy = new TH2F("fHxy", "X vs Y",200,-200,200,200,-200,200);
  fT -> Draw("y:x>>fHxy", "PDGid==-13");

  cout <<"region cut: "<< fT -> GetEntries("abs(x)<20&&abs(y)<20&&PDGid==-13") << endl;
  cout <<"region cut: "<< fT -> GetEntries("abs(x)<35&&abs(y)<20") << endl;
  cout <<"region cut: "<< fT -> GetEntries("abs(x)<sqrt(20.0)/2&&abs(y)<sqrt(20.0)/2") << endl;

  fHx   -> SetMaximum(fHx  ->GetMaximum()*1.2);
  fHy   -> SetMaximum(fHy  ->GetMaximum()*1.2);
  fHptx -> SetMaximum(fHptx->GetMaximum()*1.2);
  fHpty -> SetMaximum(fHpty->GetMaximum()*1.2);
  fHp   -> SetMaximum(fHp  ->GetMaximum()*1.2);
  fHxy  -> SetMaximum(fHxy  ->GetMaximum()*1.2);

  fHx   -> SetFillColor(3);
  fHy   -> SetFillColor(3);
  fHptx -> SetFillColor(3);
  fHpty -> SetFillColor(3);
  fHp   -> SetFillColor(3);
  fHxy   -> SetFillColor(3);
  fHxy   -> SetTitle(";mm;mm");
  fHx   -> SetXTitle("mm");
  fHy   -> SetXTitle("mm");
  fHptx -> SetXTitle("Px/Pz");
  fHpty -> SetXTitle("Py/Pz");
  fHp   -> SetXTitle("P (MeV/c)");


  //TCanvas* c1 = new TCanvas("c1","c1",10,10,1200,1200);
  TCanvas* c1 = new TCanvas("c1","c1",10,10,1800,1200);
  c1 -> Divide(4,2);
  //c1 -> Divide(2,2);

  c1 -> cd(1);
  fHx-> Draw();
  c1 -> cd(2);
  fHptx-> Draw();
  c1 -> cd(3);
  fHxdx-> Draw("cont");

  c1 -> cd(5);
  fHy-> Draw();
  c1 -> cd(6);
  fHpty-> Draw();
  c1 -> cd(7);
  fHydy-> Draw("cont");

  c1 -> cd(4);
  fHp-> Draw();
  c1 -> cd(8);
  fHxy->Draw("colz");

  c1->SaveAs("/home/had/zhangce/g-2/Hline/Otani-san/data/g4output_200605_2e6_000.pdf");
}
