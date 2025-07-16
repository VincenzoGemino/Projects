Struttura dati:
    struct data{
        int anno;
        int mese;
        int giorno;
    } data_t;

    struct ora{
        int ora;
        int minuti;
        int secondi;
    } ora_t;
    
struct tratta{
        char codice[STR];
        char partenza[STR];
        char arrivo[STR];
        char data_str[STR];
        char orap_str[STR];
        char orad_str[STR];
        int ritardo;
        data_t data;
        ora_t par, arr;
    } tratta_t;

    struct tabella{
        int n_corse;
        tratta_t log[MAXR];
    } tabella_t;

    enum comando_e{
        r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_fine;
    }

    tabella_t leggiTabella(){
        int i;
        tabella_t tab;
        FILE *fpin = fopen(FILE_IN, "r");
        if(in == NULL){
            exit(-1);
        }

        fscanf(in, "%d", &tab.n_corse);
        for(i = 0; i < tab.n_corse; i++){
            fscanf(in, "%s %s %s %s %s %s %d\n", tab.log[i].codice, tab.log[i].partenza, tab.log[i].arrivo, tab.log[i].data_str, tab.log[i].orap_str, tab.log[i].orad_str, &tab.log[i].ritardo);
            sscanf()
        }
    }
    
    int dataSTR2INT(data_t data);
    comando_e leggiComando(char comandi[][STR]){
        int i;
        char cmd[STR];
        printf("Comando > ");
        scanf("%s", cmd);
        for(i = 0; i<CMD; i++){
            if(strcmp(cmd, comandi[i]) == 0){
                return (comando_e) i;
            }
        }
        return -1;
    }


    void stampaComandi(char comandi[][STR]){
        int i;
        printf("Comandi disponibili: ");
        for(i = 0; i<CMD;i++){
            printf(" %s", comandi[i]);
        }
        printf("\n");
    }

    void stampaTratta(tratta_t t){
        printf("Tratta [%s] da %s a %s del % (dalle %s alle %s, con ritardo di %d minut%c.\n)", ..., ((t.ritardo == 1) ? 'o' : 'i');
    }
    void selezionaDati(tabella_t tab, comando_e cmd){
        data_t d1, d2;
        char target[STR];
        int i, tot = 0;
        if(cmd == r_date){
            printf("Inserire prima data [aaaa/mm/gg]: ");
            scanf("%d/%d/%d", &d1.anno, &d1.mese, &d1.giorno);
        }
    }
