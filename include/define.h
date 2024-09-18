
#define COMMUTATOR_CREAT 'c'
#define COMMUTATOR_TEST 't'
#define COMMUTATOR_FILE 'f'
#define COMMUTATOR_APPEND 'r'
#define COMMUTATOR_UPDATE 'u'
#define COMMUTATOR_EXTRAXT 'x'

typedef struct s_commutator{

    char commutator;
    void (*func)(char**, char**);
    
}t_commutator;

typedef struct tar_s{

    char origine_name[100];
    unsigned int begin;
    union{
        
        union{

            struct {
                
                char name[100];
                char mode[8];
                char unid[8];
                char gid[8];
                char size[12];
                char mtime[12];
                char check[8];
                char link;
                char link_name[100];
                char ustar[8];
                char owner[32];
                char group[32];
                char major[8];
                char minor[8];
                char prefix[115];
            };
            
        };

        char block[512];
    };

    struct tar_s* next;

}tar_t;