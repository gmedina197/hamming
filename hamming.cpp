#include <bits/stdc++.h>

using namespace std;

int* chartobin(char buffer, int oito[]){
	char a = buffer;
	int mask = 0x80, k = 0;/*10000000*/ 
	while (mask > 0) {
	    oito[k] = (a & mask) > 0;
	    mask >>= 1;
	    k++; 
	}
	return oito;
}

int* para13(int oito[], int treze[]){
	treze[2] = oito[7];
	treze[4] = oito[6];
	treze[5] = oito[5];
	treze[6] = oito[4];
	treze[8] = oito[3];
	treze[9] = oito[2];
	treze[10] = oito[1];
	treze[11] = oito[0];
	return treze;
}

int* ces(int treze[]){
	int c1 = 0, c2 = 0, c4 = 0, c8 = 0;
	c1 = treze[2] xor treze[4] xor treze[6] xor treze[8] xor treze[10];
	c2 = treze[2] xor treze[5] xor treze[6] xor treze[9] xor treze[10];
	c4 = treze[4] xor treze[5] xor treze[6] xor treze[11];
	c8 = treze[8] xor treze[9] xor treze[10] xor treze[11];
			
	treze[0] = c1;
	treze[1] = c2;
	treze[3] = c4;
	treze[7] = c8;
	treze[12] =  treze[0] xor treze[1] xor treze[2] xor treze[3] xor treze[4] xor treze[5] xor treze[6] xor treze[7] xor 
	treze[8] xor treze[9] xor treze[10] xor treze[11];
	return treze;
}

char* emes(int dezesseis[], char oito[]){
	/*m8 m7  m6  m5  c8  m4  m3 m2 c4 m1  c2 c1
	   1  2   3   4   5   6   7  8  9 10  11 12*/	
	oito[0] = dezesseis[1] + '0';
	oito[1] = dezesseis[2] + '0';
	oito[2] = dezesseis[3] + '0';
	oito[3] = dezesseis[4] + '0';
	oito[4] = dezesseis[6] + '0';
	oito[5] = dezesseis[7] + '0';
	oito[6] = dezesseis[8] + '0';
	oito[7] = dezesseis[10] + '0'; 
	return oito;
}

int flip(int nbit){
	if (nbit < 4)
		return (nbit + 4);
	else if (nbit > 3 && nbit < 7)
		return (nbit + 5);
	else if (nbit == 7)
		return (nbit + 6);
}

int main (int argc, char **argv){
	if (strcmp(argv[2],"-w") == 0){
		ifstream fileRead(argv[1]);
		ofstream fileOut(argv[3]);
		cout << argv[1] << endl;

		char buffer;
		while (fileRead.get(buffer)){	
			int oito[8], treze[13], j = 3, hamming[15];
			for (int i = 0; i < 16; i++)
				hamming[i] = 0;	
			
			cout << "Char lido: " << buffer << endl;
			/*Atribuindo vetor com o hamming*/
			cout << "Hamming: ";
			for (int i = 12; i >= 0  ; i--){
				hamming[j] = ces(para13(chartobin(buffer,oito),treze))[i]; 
				j++;
			}
			for (int i = 3; i < 16; i++)
				cout << hamming[i];
			cout << endl;
			/*-----------------------*/
			/*convertendo para 2 bytes e para char*/
			char byte1[8], byte2[8];
			for (int i = 0; i < 16; i++){	
				if (i < 8)
					byte1[i] = hamming[i] + '0';
				else
					byte2[i-8] = hamming[i] + '0';
			}
			cout << "Byte 1: ";
			for (int i = 0; i< 8; i++)
				cout << byte1[i];	
			cout << endl;
			cout << "Byte 2: ";
			for (int i = 0; i < 8; i++)
				cout << byte2[i];
			char b1 = strtol(byte1, 0, 2), b2 = strtol(byte2, 0, 2);;
			/*---------------------------*/
			fileOut << b1 << b2;
			cout << endl;
			cout << endl;
		}
		fileOut.close();
		fileRead.close();
	}else if (strcmp(argv[2], "-r") == 0){
		ifstream fileMod(argv[1]);
		ofstream fileLast(argv[3]);
		char _char, _char2;
		while (fileMod.get(_char) && fileMod.get(_char2)){
			/*juntando os bytes do arquivo modificado e do original*/
			int oito[8], byte[13], byteO[16];
			for(int i = 0; i < 8; i++){
				byteO[i] = chartobin(_char,oito)[i];
				byteO[i+8] = chartobin(_char2,oito)[i];		
			}
			for (int i = 0; i < 13; i++){
				byte[i] = byteO[i+3];
				cout << byte[i];
			}
			cout << endl;
			/*--------------------------------*/
			int c1 = byte[12], c2 = byte[11], c4 = byte[9], c8 = byte[5], g = byte[0]; /*c original*/
			int cl1 = 0, cl2 = 0, cl4 = 0, cl8 = 0, gl = 0; /*c modificado*/
			int ces[4], GX, nbit = 0, cont = 0;
			char arq, mes[8];
			/*m8 m7  m6  m5  c8  m4  m3 m2 c4 m1  c2 c1
			  1   2   3   4   5   6   7  8  9 10  11 12*/
			cl1 = byte[10] xor byte[8] xor byte[6] xor byte[4] xor byte[2];
			cl2 = byte[10] xor byte[7] xor byte[6] xor byte[3] xor byte[2];
			cl4 = byte[8] xor byte[7] xor byte[6] xor byte[1];
			cl8 = byte[4] xor byte[3] xor byte[2] xor byte[1];
			
			ces[0] = c1 xor cl1;
			ces[1] = c2 xor cl2;
			ces[2] = c4 xor cl4;
			ces[3] = c8 xor cl8;
			cout << c1 << c2 << c4 << c8 << endl;
			cout << cl1 << cl2 << cl4 << cl8 << endl;
			
			for (int i = 0; i < 4; i++)
				cout << ces[i];
			cout << endl;

			for (int i = 0; i < 4; i++){
				if (ces[i] == 1){
					cont++;
					nbit += pow(2,(3-i));
				}
			}
			for (int i = 0; i < 8; i++){
				mes[i] = emes(byte, mes)[i];/*vetor de m's*/
			}
			if (cont > 0){	
				if (byte[13-nbit] == 0) 
					byte[13-nbit] = 1;
				else 
					byte[13-nbit] = 0;	 	
			}
			gl = byte[12] xor byte[11] xor byte[10] xor byte[9] xor byte[8] xor byte[7] xor
					byte[6] xor	byte[5] xor byte[4] xor byte[3] xor byte[2] xor byte[1];
			

			cout << "g = " << g << endl;
			cout << "g'= " << gl << endl;

			GX = gl xor g;
			if (cont == 0){
				cout << "Byte sem alteração." << endl;
				arq = strtol(mes, 0, 2);
				fileLast << arq;
			}
			if (nbit > 0 && nbit < 12){
				cout<< "Posicao a ser alterada " << nbit <<endl;
				cout << "Byte corrigido." << endl;
				for (int i = 0; i < 8; i++){
					mes[i] = emes(byte, mes)[i];/*vetor de m's*/
				}
				arq = strtol(mes, 0, 2);
				fileLast << arq;
			}
			else if (GX != 0){
				cout << "ERROR: Mais de um bit alterado" << endl;
				fileLast << "BUG" << endl;
			}	
			cout << endl;		
		}
		fileLast.close();
	}
}