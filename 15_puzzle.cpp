#include<stdio.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#define size 4

int move[4][2]= {{-1,0},{0,-1},{0,1},{1,0}}; 
char op[4]= {'U','L','R','D'};
int map[size][size],map1[size][size],map2[size*size],limit,path[100];
int flag,length;//lengthΪ���յ�·������
int goal[16][2]= {{3,3},{0,0},{0,1}, {0,2},{0,3}, {1,0},
	{1,1}, {1,2}, {1,3},{2,0}, {2,1}, {2,2},{2,3},{3,0},{3,1},{3,2}
};



int solvability(int a[size*size]) { //�鿴������,�Ӷ��жϿɽ��� ,���е���ż��Ӧ�ñ��ֲ���
	int i,j,ni,w,x,y;  
	ni=0; //ni�����������
	for(i=0; i<size*size; i++) { 
		if(a[i]==0)  
			w=i;

		for(j=i+1; j<size*size; j++) {
			if(a[i]>a[j])
				ni++;
		}
	}
	x=w/size; //0���ڵĺ�����
	y=w%size;  //0���ڵ�������
	ni+=abs(x-3)+abs(y-3);  //������0��ƫ���� ��0������ӦΪ��3,3��
	if(ni%2==1)//s=perm+distΪ�����ɽ�
		return 1;
	else
		return 0;
}


void rand_generate() { //�������ʮ���� 
	int i=0;
	int m;
	memset(map2,-1,sizeof(map2));
	m=rand()%16;
	while(i<16) {
		for(int j=0; j<16; j++) {
			if(m==map2[j]) {
				m=rand()%16;
				j=0;
			}
		}
		map2[i++]=m;
		m=rand()%16;
	}

}

void default_generate() {
	int map3[16]= {1,2,3,4,5,10,6,8,0,9,7,12,13,14,11,15};
	for(int i=0; i<16; i++) {
		map2[i]=map3[i];
	}
}




int manhattan_dis(int a[][size]) { //���ۺ���(�����پ���) 
	int i,j,cost=0;
	for(i=0; i<size; i++) {
		for(j=0; j<size; j++) {
			int w=map[i][j];
			cost+=abs(i-goal[w][0])+abs(j-goal[w][1]); //(i,j)��Ŀ��λ�ý��бȽ�
		}
	}
	return cost;  //����λ�õ������پ���
}



void swap(int*a,int*b) { //��������
	int tmp;
	tmp=*a;
	*a=*b;
	*b=tmp;
}


int check() { //��������Ƿ�Ϸ�
	for(int i=0; i<16; i++) {
		for(int j=0; j<16; j++) {
			if(map2[i]==map2[j]&&i!=j)
				return 0;
		}

	}

	return 1;

}


void print() { //��ӡԪ��
	int count=0;
	for(int i=0 ; i<16; i++) {

		printf("%2d ",map2[i]);
		count++;
		if(count%4==0)
			printf("\n");

	}
}

void print_map() {
	int count=0;
	for(int i=0; i<4; i++) {
		for(int j=0; j<4; j++) {
			count++;
			printf("%2d ",map[i][j]);
			if(count%4==0)
				printf("\n");
		}
	}


}

void print_element() {
	int count=0;
	for(int i=0; i<4; i++) {
		for(int j=0; j<4; j++) {
			count++;
			printf("%2d ",map1[i][j]);
			if(count%4==0)
				printf("\n");
		}
	}


}

void print_map1(int ox,int oy) {
	int fx,fy;
	for(int i=0; i<length; i++) {
		switch(path[i]) {
			case 0:
				fx=ox+move[0][0];
				fy=oy+move[0][1];
				swap(&map1[ox][oy],&map1[fx][fy]);
				ox=fx;
				oy=fy;
				print_element();
				printf("\n");
				break;
			case 1:
				fx=ox+move[1][0];
				fy=oy+move[1][1];
				swap(&map1[ox][oy],&map1[fx][fy]);
				print_element();
				ox=fx;
				oy=fy;
				printf("\n");
				break;
			case 2:
				fx=ox+move[2][0];
				fy=oy+move[2][1];
				swap(&map1[ox][oy],&map1[fx][fy]);
				print_element();
				ox=fx;
				oy=fy;
				printf("\n");
				break;
			case 3:
				fx=ox+move[3][0];
				fy=oy+move[3][1];
				swap(&map1[ox][oy],&map1[fx][fy]);
				print_element();
				ox=fx;
				oy=fy;
				printf("\n");
				break;
			default:
				printf("\n\t\t---��������---\n");
		}


	}




}



void dfs(int ox,int oy,int len,int pre_move)
//ox,oy�ǿո��λ�� len��ʼʱΪ0 ��len��ʾ�ⷨ·���ĳ��� pre_move����iֵ����֮ǰ���ƶ�
{
	int i,fx,fy;
	if(flag)
		return;
	int dv=manhattan_dis(map); //�ƶ��ո��map�Ĵ���

	if(len==limit) {
		if(dv==0) { //dv==0˵�����������Ѿ�����Ŀ���λ��
			flag=1;
			length=len;
			return;
		} else
			return;  //����Ԥ�����ȣ����ˣ�û�н�һ�������ļ�ֵ
	}

	else if(len<limit) {
		if(dv==0) { //С��Ԥ������ ���ɹ� 
			flag=1;
			length=len;
			return;
		}
	}

	for(i=0; i<4; i++) {
		if(i+pre_move==3&&len>0)//������һ���ƶ������෴( i+pre_move==3 )��len>0��ȷ���Ѿ��ƶ�����
			continue;
		fx=ox+move[i][0];  //0 ���������ƶ�
		fy=oy+move[i][1];


		if(0<=fx&&fx<size && 0<=fy&&fy<size) { //�ж��ƶ�����
			swap(&map[ox][oy],&map[fx][fy]);  //�ƶ�0��λ��
			int p=manhattan_dis(map);   //�ƶ���������پ���

			if(p+len<=limit&&!flag) { //��֦�ж����
				path[len]=i;//i��ȡ0,1,2,3
				dfs(fx,fy,len+1,i);  //�統ǰ���ɹ��� �ݹ����dfsֱ��������������������н�
				if(flag)
					return;
			}

			swap(&map[ox][oy],&map[fx][fy]);  //������(���۹���)�����һ��
		}
	}
}



int main() {

	int i,j,k,l,m,n,ox,oy;
	i=0;
	int choice;
	while(true) {
		printf("\n1������Ĭ��ʮ���� \n\n2������ʮ����\n");
		printf("\n3���������ʮ����\n\n");
		printf("��ѡ���������: ");
		scanf("%d",&choice);
		printf("\n");
		if(choice==1) {
			default_generate();
			print();
		}


		else if(choice==2) {
			for(int i=0; i<16; i++)
				scanf("%d",&map2[i]);
			if(check()==0) {
				printf("���������ظ�������");
				return 0;
			}


		} else if(choice==3) {

			while(check()!=1) {
				rand_generate();
			}
			print();
		} else {
			printf("��������");
			return 0;

		}



		flag=0,length=0; //flag�����ж��Ƿ񵽴�Ŀ��״̬ ��length��ֵΪ0
		memset(path,-1,sizeof(path));  //�Ѷ���path[100]���飬��path����-1
		for(i=0; i<16; i++) {
			if(map2[i]==0) {
				map[i/size][i%size]=0; 
				ox=i/size;
				oy=i%size;  //ox��oy��¼0��λ��
			} else {
				map[i/size][i%size]=map2[i];  
			}

		}
		for(int i=0; i<4; i++) {
			for(int j=0; j<4; j++) {
				map1[i][j]=map[i][j];
			}
		}


		if(solvability(map2)==1) {      //��״̬�ɴ� ��������ɽ�
			limit=manhattan_dis(map);  //ȫ���������پ���֮��

			while(!flag&&length<=50) { //Ҫ��50��֮�ڵ���,·������ҪС��50
				dfs(ox,oy,0,0);
				if(!flag)
					limit++; //�ﵽlimit���Ҳ�����ֻ�ܽ�limit�ſ������
			}


			if(flag) {

				printf("\n");
				print_map1(ox,oy);
				printf("\n");
				printf("�ո���Ҫ�ߵ�·��Ϊ:");
				for(int i=0; i<length; i++)
					printf("%c ",op[path[i]]);  
				printf("\n\n");



			}
		}

		else if(!solvability(map2)||!flag)
			printf("This puzzle is not solvable.\n");
		getchar();
		printf("\n��������?(Y/N)");
		char reply = getchar();
		if(reply!='Y'&& reply != 'y')
			break;
		system("cls");
	}

	return 0;
}
