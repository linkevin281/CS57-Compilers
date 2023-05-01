extern void print(int); 
extern int read();

int func(int a){ 

        int loc1;
        int loc2;
        int i;
        int j;

        loc1 = a + 10; 
        loc2 = a * 10; 

        if (loc1 > loc2) {
                int b; 
                print(loc1); 
                a = 0;
                if (a > 0) {
                        print(a);
                }
                else {
                        print(loc2);
                }
        }
        else
                print(loc2);
                i = 0;
                b = 0;
        while (i < loc1){
                int j;
                i = i + 1;
                j = loc2 + i;
                loc2 = j;
        }

        return(loc1 + loc2);
}
