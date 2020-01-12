#pragma once

struct Element {

	int ID[4];
	double **HL;
	double **CL;
	double *PL;

	Element() {
		this->HL = new double* [4];
		this->CL = new double* [4];
		this->PL = new double [4];

		for (int i = 0; i < 4; i++) {
			this->HL[i] = new double[4];
			this->CL[i] = new double[4];
		}

		for (int i = 0; i < 4; i++) {
			this->PL[i] = 0;
			for (int j = 0; j < 4; j++) {
				this->HL[i][j] = 0;
				this->CL[i][j] = 0;
			}
		}
	}

	~Element() {
		for (int i = 0; i < 4; i++) {
			delete[] HL[i];
			delete[] CL[i];
		}
		delete HL;
		delete CL;
		delete PL;
	}

	void setID(int i, int nH) {
		ID[0] = i;
		ID[1] = ID[0] + nH;
		ID[2] = ID[1] + 1;
		ID[3] = ID[0] + 1;
	}

	void printElement(int i) {
		std::cout << "elements[" << i + 1 << "] - ID1 = " << ID[0] << ", ID2 = " << ID[1] << ", ID3 = " << ID[2] << ", ID4 = " << ID[3] << std::endl;
	}

};
