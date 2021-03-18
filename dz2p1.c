#include<stdio.h>
#include<stdlib.h>
#define MAXSTR 30
#define MAX 1000
#define COUNT 10

typedef struct Igrac {
	char ime[MAXSTR];
	char prezime[MAXSTR];
	int height;
	int redniBr;
	struct igrac* left;
	struct igrac* right;
	struct igrac* next;
} igrac;

igrac* first = NULL;
igrac* last = NULL;
igrac* root = NULL;
int high = 0;

void UnosImena(igrac** novi) {
	int i = 0;
	char c;

	printf("Unesi ime igraca: ");
	while ((c = getchar()) != '\n') {
		(*novi)->ime[i] = c;
		i++;
	}
	(*novi)->ime[i] = '\0';
}

void UnosPrezimena(igrac** novi) {
	int i = 0;
	char c;

	printf("Unesi prezime igraca: ");
	while ((c = getchar()) != '\n') {
		(*novi)->prezime[i] = c;
		i++;
	}
	(*novi)->prezime[i] = '\0';
}

void CreateQualifyQueue(igrac** niz, int kvalut, int kvalig, int n) {
	int i, j = 0;

	for (i = n - kvalig; i < n - kvalig + kvalig / 2; i++) {
		igrac* novi = niz[i];

		if (first == NULL) {
			first = novi;
			last = novi;
		}
		else {
			last->next = novi;
			last = novi;
		}

		novi = niz[n - j - 1];
		last->next = novi;
		last = novi;
		j++;
	}
}

void IspisiRed() {
	igrac* tek = first;
	printf("\n");

	while (tek != NULL) {
		if (tek->next == NULL) {
			printf("(%d) ", tek->redniBr);
			tek = tek->next;
		}
		else {
			printf("(%d) -> ", tek->redniBr);
			tek = tek->next;
		}
	}

	printf("\n");
}

void Push(igrac* cvor) {
	igrac* novi = cvor;

	if (first == NULL){
		first = novi;
		last = novi;
	}	
	else {
		last->next = novi;
		last = novi;
	}
}

igrac* Pop() {
	igrac* tmp = first;
	
	if (first == last) {
		first = NULL;
		last = NULL;
	}
	else 
		first = first->next;
	
	return tmp;
}

void PossibleMatch() {

	int cont1, cont2;
	igrac* now = first;

	while (now != NULL) {
		cont1 = now->redniBr;
		now = now->next;
		if (now != NULL) {

			cont2 = now->redniBr;
			printf("Moguci par: (%d) -> (%d)\n", cont1, cont2);

			now = now->next;
		}
	}
}

void CreateTree(igrac** niz, int kvalut, int kvalig, int n, int numMatch) {
	igrac* pom1 = malloc(sizeof(igrac));
	igrac* pom2 = malloc(sizeof(igrac));
	igrac* tek = first;
	igrac* old;
	int g, i = 0, kvalifikacije = 0;
	int j, pom = 0, izbaceni, choice1;
	
	izbaceni = kvalig;
	while (tek != NULL || kvalifikacije != numMatch) {		
		printf("Moguci parovi?\n"
			"1. Da.\n"
			"2. Ne.\n"
			"Vas izbor? ");
		scanf("%d", &choice1);
		switch (choice1) {
		case 1:
			PossibleMatch();
			break;
		case 2:
			break;
		}

		g = 0;
		pom1 = Pop();
		pom2 = Pop();
		tek = first;
		igrac* unutrasnji = malloc(sizeof(igrac));

		unutrasnji->left = pom1;
		unutrasnji->right = pom2;
		unutrasnji->next = NULL;
		printf("Pobednik utakmice izmedju %d. i %d. je: ", pom1->redniBr, pom2->redniBr);
		while (g == 0) {
			scanf("%d", &unutrasnji->redniBr);
			if (unutrasnji->redniBr != pom1->redniBr && unutrasnji->redniBr != pom2->redniBr) {
				g = 0;
				printf("Pokusaj ponovo: ");
			}
			else
				g = -1;
		}
		kvalifikacije++;

		printf("\n");

		Push(unutrasnji);
		if (kvalifikacije <= kvalut && izbaceni < n) {
			Push(niz[i]);
			izbaceni++;
			i++;
			if (kvalifikacije + 1 > kvalut)
				pom++;
		}
		else
			pom++;

		if (pom == 1 && izbaceni < n) {
			if (n % 2 == 1 && kvalut != 1)
				for (j = 1; i <= (n - kvalig) / 2 + 1; i++) {
					Push(niz[i]);
					Push(niz[n - kvalig - j]);
					j++;
				}
			else
				for (j = 1; i < (n - kvalig) / 2 + 1; i++) {
					Push(niz[i]);
					Push(niz[n - kvalig - j]);
					j++;
				}
		}
	}

	printf("\n");
	root = Pop();
	printf("Pobednik je igrac sa rednim brojem (%d)!\n", root->redniBr);
}

void print2DUtil(igrac* root, int space) {
	// Base case 
	if (root == NULL)
		return;

	// Increase distance between levels 
	space += COUNT;

	// Process right child first 
	print2DUtil(root->right, space);

	// Print current node after space 
	// count 
	printf("\n");
	for (int i = COUNT; i < space; i++)
		printf(" ");
	printf("%d\n", root->redniBr);

	// Process left child 
	print2DUtil(root->left, space);
}

void print2D(igrac *root)
{
	// Pass initial space count as 0 
	print2DUtil(root, 0);
}

void LevelOrder(int numNode, int n) {
	if (root == NULL)
		return;

	int pom1[COUNT], pom2[COUNT];
	int match = 0, g = 0, i;
	pom1[0] = 0;
	pom2[0] = 1;

	for (i = 1; i < COUNT; i++) {
		pom1[i] = pom1[i - 1] + 1;
		pom2[i] = pom2[i - 1] * 2;
	}
	pom2[0] = 0;
	i = 0;

	Push(root);
	
	while (first != NULL) {
		igrac* tek = first;

		if (tek->left != NULL)
			Push(tek->left);
		if (tek->right != NULL)
			Push(tek->right);

		Pop();
		tek->height = high;
		printf("%d ", tek->redniBr);
		
		if (match == pom2[i] && g == pom1[i]) {
			printf("\n");
			match = 0;
			g++;
			i++;
			high++;
		}
		
		
		numNode++;
 		match++;
	}
	printf("\n");
	printf("Broj cvorova je: %d\n", numNode);
}

void ShowRound(igrac* root) {
	int choice;

	printf("Koju rundu zelite da vidite? ");
	scanf("%d", &choice);

	Push(root);
	while (first != NULL) {

		if (root->left != NULL)
			Push(root->left);
		if (root->right != NULL)
			Push(root->right);
		
		root = Pop();
		if (root->height == high + 1 - choice)
			printf("%d ", root->redniBr);
	}
	printf("\n");
}

void DeleteTree() {
	if (root == NULL)
		return;

	Push(root);
	while (first != NULL) {
		igrac* tek = first;
		igrac* old;

		if (tek->left != NULL)
			Push(tek->left);
		if (tek->right != NULL)
			Push(tek->right);

		old = Pop();
		free(old);
	}
	root = NULL;
}

int main() {
	
	int n, i, maxstep2 = 1, kvalut, kvalig, numMatch, choice, space = 0;
	int numNode = 0;
	igrac* niz[MAX];

	igrac* cvor = NULL;

	while (1) {

		printf("1. Unesite igrace.\n"
			"2. Ispisi kvalifikacije.\n"
			"3. Napravi stablo i odredi pobednika.\n"
			"4. Ispisi stablo.\n"
			"5. Odredi broj cvorova i ispisi stablo level orderom.\n"
			"6. Obrisi stablo.\n"
			"0. Izadji iz programa.\n"
			"Vas izbor? ");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			printf("Broj igraca: ");
			scanf("%d", &n);
			getchar();
			while (maxstep2 <= n)
				maxstep2 *= 2;
			maxstep2 /= 2;
			kvalut = n - maxstep2;
			kvalig = kvalut * 2;
			numMatch = kvalut + maxstep2 - 1;

			if (kvalut == 0) {
				kvalig = n;
			}

			for (i = 0; i < n; i++) {
				igrac* novi = malloc(sizeof(igrac));
				novi->redniBr = i + 1;
				UnosImena(&novi);
				UnosPrezimena(&novi);
				novi->height = 0;
				novi->left = NULL;
				novi->right = NULL;
				novi->next = NULL;
				printf("\n");

				niz[i] = novi;
			}

			CreateQualifyQueue(&niz, kvalut, kvalig, n);
			break;

		case 2:
			IspisiRed();
			break;

		case 3:
			CreateTree(&niz, kvalut, kvalig, n, numMatch);
			break;

		case 4:
			print2D(root);
			break;
		
		case 5:
			LevelOrder(numNode, n);
			ShowRound(root);
			break;

		case 6:
			DeleteTree();
			break;

		case 0:
			exit(0);
		}
	}	
}