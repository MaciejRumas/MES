#pragma once

struct Element {

	int ID[4];

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