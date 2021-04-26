#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>

#include "TROOT.h"
#include "TFile.h"
#include "TDirectoryFile.h"
#include "TTree.h"

int main(int argc, char **argv) {

    if (argc < 3 || argc > 4) {
        std::cout
            << "usage:\n\t"
            << argv[0]
            << " <in_file> <out_file> [<nEvents>]"
            << std::endl;
        return -1;
    }

    size_t N = std::numeric_limits<size_t>::max();

    if (argc == 4) {
        N = std::atoi(argv[3]);
    }

    std::ofstream outfile;
    outfile.open(argv[2]);

    TFile *infile = new TFile(argv[1], "READ");
    TDirectoryFile *dir;
    infile->GetObject("aod2microtuple", dir);
    TTree *Events;
    dir->GetObject("Events", Events);

    UInt_t nElectron;
    Events->SetBranchAddress("nElectron", &nElectron);
    UInt_t nMuon;
    Events->SetBranchAddress("nMuon", &nMuon);
    UInt_t nJet;
    Events->SetBranchAddress("nJet", &nJet);

    Float_t *Electron_pt = new Float_t[100];
    Events->SetBranchAddress("Electron_pt", Electron_pt);
    Float_t *Electron_eta = new Float_t[100];
    Events->SetBranchAddress("Electron_eta", Electron_eta);
    Float_t *Electron_phi = new Float_t[100];
    Events->SetBranchAddress("Electron_phi", Electron_phi);
    Int_t *Electron_charge = new Int_t[100];
    Events->SetBranchAddress("Electron_charge", Electron_charge);

    Float_t *Muon_pt = new Float_t[100];
    Events->SetBranchAddress("Muon_pt", Muon_pt);
    Float_t *Muon_eta = new Float_t[100];
    Events->SetBranchAddress("Muon_eta", Muon_eta);
    Float_t *Muon_phi = new Float_t[100];
    Events->SetBranchAddress("Muon_phi", Muon_phi);
    Int_t *Muon_charge = new Int_t[100];
    Events->SetBranchAddress("Muon_charge", Muon_charge);

    Float_t *Jet_pt = new Float_t[100];
    Events->SetBranchAddress("Jet_pt", Jet_pt);
    Float_t *Jet_eta = new Float_t[100];
    Events->SetBranchAddress("Jet_eta", Jet_eta);
    Float_t *Jet_phi = new Float_t[100];
    Events->SetBranchAddress("Jet_phi", Jet_phi);
    Float_t *Jet_mass = new Float_t[100];
    Events->SetBranchAddress("Jet_mass", Jet_mass);
    Float_t *Jet_btag = new Float_t[100];
    Events->SetBranchAddress("Jet_btag", Jet_btag);

    Float_t MET_pt;
    Events->SetBranchAddress("MET_pt", &MET_pt);
    Float_t MET_phi;
    Events->SetBranchAddress("MET_phi", &MET_phi);

    

    for (size_t i = 0; i < std::min<size_t>(N, Events->GetEntries()); i++) {
        Events->GetEntry(i);

        size_t j = 0;
        outfile << j++ << ' ' << i+1 << " 0" << std::endl;

        for (size_t k = 0; k < nElectron; k++) {
            outfile << j++ << ' '
                << 1 << ' '
                << Electron_eta[k] << ' '
                << Electron_phi[k] << ' '
                << Electron_pt[k] << ' '
                << 0.0f << ' '
                << Electron_charge[k] << ' '
                << 0.0f << ' '
                << 0.0f << ' '
                << 0.0f << ' '
                << 0.0f << ' '
                << std::endl;
        }

        for (size_t k = 0; k < nMuon; k++) {
            outfile << j++ << ' '
                << 2 << ' '
                << Muon_eta[k] << ' '
                << Muon_phi[k] << ' '
                << Muon_pt[k] << ' '
                << 0.0f << ' '
                << Muon_charge[k] << ' '
                << 0.0f << ' '
                << 0.0f << ' '
                << 0.0f << ' '
                << 0.0f << ' '
                << std::endl;
        }

        for (size_t k = 0; k < nJet; k++) {
            outfile << j++ << ' '
                << 4 << ' '
                << Jet_eta[k] << ' '
                << Jet_phi[k] << ' '
                << Jet_pt[k] << ' '
                << Jet_mass[k] << ' '
                << 0.0f << ' '
                << 0 << ' ' // !!!
                << 0.0f << ' '
                << 0.0f << ' '
                << 0.0f << ' '
                << std::endl;
        }
        
        outfile << j++ << ' '
                << 6 << ' '
                << 0.0f << ' '
                << MET_phi << ' '
                << MET_pt << ' '
                << 0.0f << ' '
                << 0.0f << ' '
                << 0.0f << ' '
                << 0.0f << ' '
                << 0.0f << ' '
                << 0.0f << ' '
                << std::endl;
    }

    delete Electron_pt;
    delete Electron_eta;
    delete Electron_phi;
    delete Electron_charge;

    delete Muon_pt;
    delete Muon_eta;
    delete Muon_phi;
    delete Muon_charge;

    delete Jet_pt;
    delete Jet_eta;
    delete Jet_phi;
    delete Jet_mass;
    delete Jet_btag;

    infile->Close();
    outfile.close();
    return 0;
}
