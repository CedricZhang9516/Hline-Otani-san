//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun Feb  1 10:20:47 2015 by ROOT version 5.34/13
// from TTree focus_det_5/VirtualDetector/focus_det_5
// found on file: G-2EDM_output_test1000.root
//////////////////////////////////////////////////////////

#ifndef dump_h
#define dump_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

string filename;
//const string outputfile = "150201_surfmu_at_focus.dat";
//const string outputfile = "150216_surfmu_at_focus_aftertune.dat";
//const string outputfile = "150223_surfmu_at_focus_aftertune_p36init_re.dat";
//const string outputfile = "150315_surfmu_at_focus_aftertune_p36init_sepON.dat";
//const string outputfile = "150324_surfmu_at_focus_aftertune_p36init_sepON_2e7.dat";
string outputfile;

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class dump {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Float_t         x;
   Float_t         y;
   Float_t         z;
   Float_t         Px;
   Float_t         Py;
   Float_t         Pz;
   Float_t         t;
   Float_t         PDGid;
   Float_t         EventID;
   Float_t         TrackID;
   Float_t         ParentID;
   Float_t         Weight;

   // List of branches
   TBranch        *b_x;   //!
   TBranch        *b_y;   //!
   TBranch        *b_z;   //!
   TBranch        *b_Px;   //!
   TBranch        *b_Py;   //!
   TBranch        *b_Pz;   //!
   TBranch        *b_t;   //!
   TBranch        *b_PDGid;   //!
   TBranch        *b_EventID;   //!
   TBranch        *b_TrackID;   //!
   TBranch        *b_ParentID;   //!
   TBranch        *b_Weight;   //!

   //dump(TTree *tree=0);
   //dump(string fname, TTree *tree=0);
   dump(string fname, string _output, TTree *tree=0);
   virtual ~dump();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef dump_cxx
//dump::dump(TTree *tree) : fChain(0) 
//dump::dump(string fname,TTree *tree) : fChain(0) 
dump::dump(string fname, string _output, TTree *tree) : fChain(0) 
{
  filename = fname;
  outputfile   = _output;
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
     //TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("G-2EDM_output_test1000.root");
     TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject(filename.c_str());
      if (!f || !f->IsOpen()) {
	//f = new TFile("G-2EDM_output_test1000.root");
	f = new TFile(filename.c_str());
      }
      //TDirectory * dir = (TDirectory*)f->Get("G-2EDM_output_test1000.root:/VirtualDetector");
      TDirectory * dir = (TDirectory*)f->Get(Form("%s:/VirtualDetector",filename.c_str()));
      dir->GetObject("focus_det_5",tree);

   }
   Init(tree);
}

dump::~dump()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t dump::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t dump::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void dump::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("x", &x, &b_x);
   fChain->SetBranchAddress("y", &y, &b_y);
   fChain->SetBranchAddress("z", &z, &b_z);
   fChain->SetBranchAddress("Px", &Px, &b_Px);
   fChain->SetBranchAddress("Py", &Py, &b_Py);
   fChain->SetBranchAddress("Pz", &Pz, &b_Pz);
   fChain->SetBranchAddress("t", &t, &b_t);
   fChain->SetBranchAddress("PDGid", &PDGid, &b_PDGid);
   fChain->SetBranchAddress("EventID", &EventID, &b_EventID);
   fChain->SetBranchAddress("TrackID", &TrackID, &b_TrackID);
   fChain->SetBranchAddress("ParentID", &ParentID, &b_ParentID);
   fChain->SetBranchAddress("Weight", &Weight, &b_Weight);
   Notify();
}

Bool_t dump::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void dump::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t dump::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef dump_cxx
