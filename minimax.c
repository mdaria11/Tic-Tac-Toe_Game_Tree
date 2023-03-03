#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//structuri

struct nodetree
{
    char tablatree[3][3], juc;
    int poz[10][2], nivel;
    struct nodetree* child[10];
};

struct nodetreess
{
    char tablatree[3][3], juc, tip[5], agr;
    int poz[10][2], nivel;
    struct nodetreess* child[10];
};

struct nodetreemini
{
    char tip;
    int val, nivel;
    struct nodetreemini* child[200];
};

struct tree
{
    struct nodetree *root;
};

struct treess
{
    struct nodetreess *root;
};

struct treemini
{
    struct nodetreemini *root;
};

//structuri

void addtree(struct nodetree *nou, char tabla[][3], char juc, int nivel, struct tree *arbore) //functie care adauga in nodul nou din arbore jocul din tabla si face urmatoarele posibilitati
{
    int i, j, finish=0, aux=0, lin, col;
    
    for(i=0; i<=9; i++) //initializam tabla din nod cu 0-uri
    {
        for(j=0; j<=1; j++)
        {
            nou->poz[i][j]=0;
        }
    }

    nou->juc=juc; //punem jucatorul care trebuie sa mute in nod
    nou->nivel=nivel; //punem nivelul nodului in nod

    for(i=0; i<=2; i++) //punem in nod tabla jocului
    {
        for(j=0; j<=2; j++)
        {
            nou->tablatree[i][j]=tabla[i][j];
        }
    }

    for(i=0; i<=2; i++)
    {
        if(nou->tablatree[i][0]==nou->tablatree[i][1] && nou->tablatree[i][1]==nou->tablatree[i][2] && nou->tablatree[i][2]!='-') //verificam castigul pe linii
        {
            finish=1;
        }
    }

    for(i=0; i<=2; i++)
    {
        if(nou->tablatree[0][i]==nou->tablatree[1][i] && nou->tablatree[1][i]==nou->tablatree[2][i] && nou->tablatree[2][i]!='-') // verificam castigul pe coloane
        {
            finish=1;
        }
    }

    if(nou->tablatree[0][0]==nou->tablatree[1][1] && nou->tablatree[1][1]==nou->tablatree[2][2] && nou->tablatree[2][2]!='-') // verificam castigul pe diagonala principala
    {
        finish=1;
    }

    if(nou->tablatree[2][0]==nou->tablatree[1][1] && nou->tablatree[1][1]==nou->tablatree[0][2] && nou->tablatree[0][2]!='-') // verificam castigul pe diagonala secundara
    {
        finish=1;
    }

    if(finish==1) //cazul in care jocul e castigat de X sau O
    {
        nou->child[0]=NULL; //nodul nu mai are niciun copil
        return;
    }
    else //cazul in care avem remiza / joc neterminat
    {
        for(i=0; i<=2; i++) //luam pozitiile libere si le trecem in matricea poz din nodul respectiv
        {
            for(j=0; j<=2; j++)
            {
                if(nou->tablatree[i][j]=='-')
                {
                    nou->poz[aux][0]=i;
                    nou->poz[aux][1]=j;
                    aux++;
                }
            }
        }

        aux--;
        nou->child[aux+1]=NULL;

        for(i=0; i<=aux; i++) //luam fiecare pozitie libera din matricea poz
        {
            lin=nou->poz[i][0];
            col=nou->poz[i][1];
            tabla[lin][col]=nou->juc; //punem jucatorul pe pozitia libera
            nou->child[i]=malloc(sizeof(struct nodetree));

            if(juc=='X') //reapelam pentru noua tabla si nodul copil
            {
                addtree(nou->child[i], tabla, 'O', nivel+1, arbore);
            }
            else
            {
                addtree(nou->child[i], tabla, 'X', nivel+1, arbore);
            }

            tabla[lin][col]='-'; //refacem tabla pt urmatorii copii
        }
    }
}

void afisaretree(struct nodetree *flag, FILE *output) //functia de afisare
{
    int i, j, ind=0, k;

    if(flag==NULL)
    {
        return;
    }
    else
    {
        for(i=0; i<=2; i++) //pt fiecare linie din tabla
        {
            for(k=0; k<flag->nivel; k++) //punem \t in functie de nivelul nodului
            {
                fputc('\t', output);
            }

            for(j=0; j<2; j++) //punem linia din joc
            {
                fputc(flag->tablatree[i][j], output);
                fputc(' ', output);
            }

            fputc(flag->tablatree[i][j], output);
            fputc('\n', output);
        }

        fputc('\n', output);

        while(flag->child[ind]!=NULL) //reapelam pentru fiecare copil
        {
            afisaretree(flag->child[ind], output);
            ind++;
        }
    }
}

void freenode(struct nodetree *flag) //functie de eliberare noduri
{
    int ind=0;

    if(flag==NULL)
    {
        return;
    }
    else
    {
        while(flag->child[ind]!=NULL) //reapelam pentru fiecare copil
        {
            freenode(flag->child[ind]);
            ind++;
        }

        free(flag); //eliberam nodul
    }
}

void cerinta1(char *in, char *out)
{
    FILE *input, *output;
    char juc[3], tabla[3][3], line[10], jucc;
    int i, j, aux, nivel=0;
    struct tree *arbore;

    arbore=malloc(sizeof(struct tree)); //initializam arborele
    arbore->root=NULL;
    input=fopen(in, "r");
    fgets(juc, 5, input); //citim jucatorul
    jucc=juc[0];

    for(i=0; i<=2; i++) //luam jocul initial din fisier
    {
        aux=0;
        fgets(line, 10, input);

        for(j=0; j<=2; j++)
        {
            tabla[i][j]=line[aux];
            aux=aux+2;
        }
    }

    arbore->root=malloc(sizeof(struct nodetree)); 
    addtree(arbore->root, tabla, jucc, nivel, arbore); //apelam functia cu root-ul
    output=fopen(out, "w");
    afisaretree(arbore->root, output); //afisam arborele
    freenode(arbore->root); //eliberam alocarile
    free(arbore);
    fclose(output); //inchidem fisierele
    fclose(input);
}

void addtreess(struct nodetreess *nou, char tabla[][3], char juc, int nivel, struct treess *arbore, char pov) //asemanator cu addtree cu diferenta ca adaugam tipul SI sau SAU plus T sau F la nodurile frunza
{
    int i, j, finish=0, aux=0, lin, col;

    for(i=0; i<=9; i++)
    {
        for(j=0; j<=1; j++)
        {
            nou->poz[i][j]=0;
        }
    }

    nou->juc=juc;
    nou->nivel=nivel;
    nou->agr='N'; //initial nodurile interne au N in loc de T sau F 

    if(juc==pov)
    {
        strcpy(nou->tip, "SAU"); //daca e randul jucatorului
        nou->tip[3]='\0';
    }
    else
    {
        strcpy(nou->tip, "SI"); //daca e randul adversarului
        nou->tip[2]='\0';
    }

    for(i=0; i<=2; i++)
    {
        for(j=0; j<=2; j++)
        {
            nou->tablatree[i][j]=tabla[i][j];
        }
    }

    for(i=0; i<=2; i++)
    {
        if(nou->tablatree[i][0]==nou->tablatree[i][1] && nou->tablatree[i][1]==nou->tablatree[i][2] && nou->tablatree[i][2]!='-') //linii
        {
            finish=1;
        }
    }

    for(i=0; i<=2; i++)
    {
        if(nou->tablatree[0][i]==nou->tablatree[1][i] && nou->tablatree[1][i]==nou->tablatree[2][i] && nou->tablatree[2][i]!='-') //coloane
        {
            finish=1;
        }
    }

    if(nou->tablatree[0][0]==nou->tablatree[1][1] && nou->tablatree[1][1]==nou->tablatree[2][2] && nou->tablatree[2][2]!='-') //diagonala principala
    {
        finish=1;
    }

    if(nou->tablatree[2][0]==nou->tablatree[1][1] && nou->tablatree[1][1]==nou->tablatree[0][2] && nou->tablatree[0][2]!='-') //diagonala secundara
    {
        finish=1;
    }

    if(finish==1) //joc terminat
    {
        nou->child[0]=NULL;

        if(nou->juc==pov) //castiga adversarul
        {
            nou->agr='F';
            return;
        }

        nou->agr='T'; //castiga jucatorul
        return;
    }
    else
    {
        for(i=0; i<=2; i++)
        {
            for(j=0; j<=2; j++)
            {
                if(nou->tablatree[i][j]=='-')
                {
                    nou->poz[aux][0]=i;
                    nou->poz[aux][1]=j;
                    aux++;
                }
            }
        }

        aux--;
        nou->child[aux+1]=NULL;

        if(aux==-1) //cazul remiza
        {
            nou->agr='F';
        }

        for(i=0; i<=aux; i++)
        {
            lin=nou->poz[i][0];
            col=nou->poz[i][1];
            tabla[lin][col]=nou->juc;
            nou->child[i]=malloc(sizeof(struct nodetree));

            if(juc=='X')
            {
                addtreess(nou->child[i], tabla, 'O', nivel+1, arbore, pov);
            }
            else
            {
                addtreess(nou->child[i], tabla, 'X', nivel+1, arbore, pov);
            }
            
            tabla[lin][col]='-';
        }
    }
}

void completare(struct nodetreess *flag) //functie care completeaza restul nodurilor interne
{
    int ind=0;

    if(flag->agr!='N')
    {
        return;
    }
    else
    {
        while(flag->child[ind]!=NULL)
        {
            if(flag->child[ind]->agr=='N') //reapelam functia pentru nodurile interne cu copiii noduri interne
            {
                completare(flag->child[ind]);
            }

            ind++;
        }

        if(strcmp(flag->tip, "SAU")==0) //caz nod de tip SAU
        {
            ind=0;

            while(flag->child[ind]!=NULL) //verifica toate nodurile copii
            {
                if(flag->child[ind]->agr=='T') //daca gaseste un copil T
                {
                    flag->agr='T';
                    return;
                }

                ind++;
            }

            flag->agr='F'; //cazul in care nodul nu are nici macar un copil T
            return;
        }
        else //cazul nod SI
        {
            ind=0;

            while(flag->child[ind]!=NULL) //verifica toate nodurile
            {
                if(flag->child[ind]->agr=='F') //cazul in care gaseste un nod F
                {
                    flag->agr='F';
                    return;
                }

                ind++;
            }

            flag->agr='T'; //caz toate nodurile copii au fost T
            return;
        }
    }
}

void afisaretreess(struct nodetreess *flag, FILE *output) //functie de afisare
{
    int ind=0, k;

    if(flag==NULL)
    {
        return;
    }
    else
    {
        for(k=0; k<flag->nivel; k++) //punem tab-urile
        {
            fputc('\t', output);
        }

        fputc(flag->agr, output); //afisam T sau F
        fputc('\n', output);

        while(flag->child[ind]!=NULL) //reapelam pentru copii
        {
            afisaretreess(flag->child[ind], output);
            ind++;
        }
    }
}

void freenodess(struct nodetreess *flag) //functie care elibereaza nodurile din arbore
{
    int ind=0;

    if(flag==NULL)
    {
        return;
    }
    else
    {
        while(flag->child[ind]!=NULL)
        {
            freenodess(flag->child[ind]);
            ind++;
        }

        free(flag);
    }
}

void cerinta2(char *in, char *out)
{
    FILE *input, *output;
    char juc[3], tabla[3][3], line[10], jucc, pov;
    int i, j, aux, nivel=0;
    struct treess *arbore;

    arbore=malloc(sizeof(struct treess)); //arborele
    arbore->root=NULL;
    input=fopen(in, "r");
    fgets(juc, 5, input); //luam jucatorul
    jucc=juc[0];
    pov=jucc; // jucatorul de la care completam F sau T 

    for(i=0; i<=2; i++) //luam jocul initial din fisier
    {
        aux=0;
        fgets(line, 10, input);

        for(j=0; j<=2; j++)
        {
            tabla[i][j]=line[aux];
            aux=aux+2;
        }
    }

    arbore->root=malloc(sizeof(struct nodetreess));
    addtreess(arbore->root, tabla, jucc, nivel, arbore, pov); //apelam pt root
    completare(arbore->root); //completam arborele
    output=fopen(out, "w");
    afisaretreess(arbore->root, output); //afisam arborele
    freenodess(arbore->root); //eliberam nodurile
    free(arbore);
    fclose(output); //inchidem fisierele
    fclose(input);
}

void nivelare(struct nodetreemini *flag, int nivel, char tip) //functie care adauga nivelul si tipul nodului (max sau min)
{
    int ind=0;

    flag->nivel=nivel;
    flag->tip=tip;

    while(flag->child[ind]!=NULL) //pentru fiecare copil
    {
        if(flag->tip=='M') //daca nodul este Max atunci copiii o sa fie Min si invers
        {
            nivelare(flag->child[ind], nivel+1, 'm');
        }
        else
        {
            nivelare(flag->child[ind], nivel+1, 'M');
        }

        ind++;
    }
}

void minimax(struct nodetreemini *flag) //functie care adauga valorile corespunzatoare nodurile in functie de tipul lor
{
    int ind=0, mmin=9999, mmax=-9999;

    while(flag->child[ind]!=NULL) //verificam ca toti copiii sa aiba valorile adevarate
    {
        if(flag->child[ind]->val==999)
        {
            minimax(flag->child[ind]);
        }

        ind++;
    }

    ind=0;

    if(flag->tip=='M') //caz nod Max
    {
        while(flag->child[ind]!=NULL) //aflam maximul dintre valorile copiilor
        {
            if(flag->child[ind]->val>=mmax)
            {
                mmax=flag->child[ind]->val;
            }

            ind++;
        }

        flag->val=mmax; //punem maximul in nod
    }
    else //caz nod minim
    {
        while(flag->child[ind]!=NULL) //aflam minimul dintre copii
        {
            if(flag->child[ind]->val<=mmin)
            {
                mmin=flag->child[ind]->val;
            }

            ind++;
        }

        flag->val=mmin; //salvam minimul in nod
    }
}

void afisaretreemini(struct nodetreemini *flag, FILE *output) //functie care afiseaza valorile (ft asemanatoare cu afisarea de la cerinta 2)
{
    int ind=0, k;

    for(k=0; k<flag->nivel; k++)
    {
        fputc('\t', output);
    }

    fprintf(output, "%d", flag->val);
    fputc('\n', output);

    while(flag->child[ind]!=NULL) //reapelare pt toti copiii
    {
        afisaretreemini(flag->child[ind], output);
        ind++;
    }
}

void freenodemini(struct nodetreemini *flag) //functie care elibereaza nodurile din arbore
{
    int ind=0;

    while(flag->child[ind]!=NULL)
    {
        freenodemini(flag->child[ind]);
        ind++;
    }

    free(flag);
}

void cerinta3(char *in, char *out)
{
    FILE *input, *output;
    char skip1, skip2, v;
    int h=0, numar, k, aux=0, st=0;
    struct treemini *arbore;
    struct nodetreemini* *vn;

    arbore=malloc(sizeof( struct treemini)); //arbore
    vn=malloc(sizeof(struct nodetreemini*)*100000); //vectorul de noduri
    input=fopen(in, "r");
    fscanf(input, "%d", &h);
    fscanf(input, "%c", &skip1);
    arbore->root=malloc(sizeof(struct nodetreemini));
    vn[aux]=arbore->root; //punem root-ul ca prim nod in vector

    while(fscanf(input, "%c %d %c", &v, &numar, &skip1)!=EOF) //cat timp avem numere in fisier
    {
        fscanf(input, "%c", &skip2);
        vn[st]->val=999; //dam nodului o valoare imposibila

        if(v=='[') //caz numar care indica valoare nodului
        {
            vn[st]->val=numar; //punem valoarea in nod
            vn[st]->child[0]=NULL; //nu mai are niciun copil
        }
        else //caz numar care indica numarul de copii
        {
            k=0;
                   	
            while(k<numar) //pentru toti copiii
            { 
                vn[st]->child[k]=malloc(sizeof(struct nodetreemini)); //alocam memorie pt fiecare copil
                aux++;
                vn[aux]=vn[st]->child[k]; //adaugam nodul in vector
                k++;
            }

            vn[st]->child[numar]=NULL;
        }
        
        st++;
    }

    nivelare(arbore->root, 0, 'M'); //completam arborele cu nivelele si tipul nodurilor
    minimax(arbore->root); //completam valorile din noduri
    output=fopen(out, "w");
    afisaretreemini(arbore->root, output); //afisam valorile
    freenodemini(arbore->root); //eliberam nodurile
    free(arbore);
    fclose(output);
    fclose(input);
    free(vn);
}

int main( int argc, char *argv[] )
{
   if(strcmp(argv[1], "-c1")==0) //prima cerinta
   {
       cerinta1(argv[2], argv[3]);
   }

   if(strcmp(argv[1], "-c2")==0) //a doua cerinta
   {
       cerinta2(argv[2], argv[3]);
   }

   if(strcmp(argv[1], "-c3")==0) //a treia cerinta
   {
       cerinta3(argv[2], argv[3]);
   }

   return 0;
}
