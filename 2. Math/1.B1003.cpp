#include<cstdio>
#include<cstring>
int main(){
    int T;
    scanf("%d", &T);
    while(T--){
        char str[110];
        scanf("%s", str);
        int len = strlen(str);
        int num_p = 0, num_t = 0,num_other=0;
        int loc_p=-1, loc_t=-1;//记录p与t的位置
        for (int i = 0; i < len; i++){
            if(str[i]=='P'){
                num_p++;
                loc_p = i;
            }
            else if(str[i]=='T'){
                num_t++;
                loc_t = i;
            }
            else if(str[i]!='A'){
                num_other++;
            }
        }
        if(num_other!=0||num_t!=1||num_p!=1||loc_t-loc_p<=1){//P和T之间不能没有字符A
            printf("No\n");
            continue;
        }
        int x = loc_p, y = loc_t - loc_p - 1, z = len - loc_t - 1;
        if(z-x*(y-1)==x){
            printf("YES\n");
        }else{
            printf("No\n");
        }
    }
    return 0;
}