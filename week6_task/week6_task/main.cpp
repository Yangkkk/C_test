/*
ħ���ռ���
by ������  1300012819
*/

#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
using namespace std;

/*
char* warrior::name[5] = {"dragon", "ninja", "iceman", "lion", "wolf"};
�췽˾����� iceman��lion��wolf��ninja��dragon ��˳��������ʿ��
����˾����� lion��dragon��ninja��iceman��wolf ��˳��������ʿ��
������ţ�0 sword, 1 bomb, 2 arrow��
*/

int chour = 0, cmin = 0;//ʱ�䣺Сʱ������
int M, N, R, K, T;//M��˾���ʼ����Ԫ����N�����и����� R:arrow������
//K: lion�ҳ϶Ƚ��ͷ��ȣ�T��ʱ�䷶Χ


class warrior;

class head{
private:
	int life, color, num;//����ֵ����ɫ����ʿ����
	int enemy;//����˾��ĵ��˵�����
	warrior * pwarrior[1000];
	friend class warrior;
	friend class dragon;
	friend class ninja;
	friend class iceman;
	friend class lion;
	friend class wolf;
	friend class city;

public:
	int pre_life;//���ڼ�¼ս����Ӹ��������ջ�����Ԫ֮ǰ������ֵ����Ϊ��ʿ���н���ʱʹ�ø�����ֵ
	warrior* occupy;//����˾��ĵ��ˡ�������ʿ�ڵ���Է�˾�����Ҫ�������������Խ���洢�ڴˡ�
	static char * cname[2];//��ɫ��Ӧ�ַ���red��blue
	static int ord[2][5];//������ʿ��˳��
	head(int ccolor) :color(ccolor){
		life = 0;
		enemy = 0;
		num = 0;
		for (int i = 0; i < 1000; ++i)
			pwarrior[i] = NULL;
		pre_life = 0;
		occupy = NULL;
	}
	void init(int clife){//��ʼ������
		enemy = 0;
		life = clife;
		pre_life = 0;
		occupy = NULL;
		for (int i = 0; i <= num; ++i)
			pwarrior[i] = NULL;
		num = 0;
	}
	~head();
	int getenemy(){
		return enemy;
	}
	int getlife(){
		return life;
	}
	void addenemy(warrior* p){
		++enemy;
		occupy = p;
	}
	//����Ϊ������Ӧ��Ԫ��ֵ
	void changelife(int n){
		life += n;
	}
	void set_pre_life(){
		pre_life = life;
	}
	void produce();//������ʿ
	void reportlife(){
		printf("%03d:%02d %d elements in %s headquarter\n", chour, cmin, life, cname[color]);
	}
};
head redhead(0);//��˾�
head bluehead(1);//��˾�


class city{
private:
	int num;//���б��
	int flag;//0��û���죬 1�����죬2������
	int life;//���е�����Ԫ
	warrior* redwarrior;//�����к���ʿ��û����ΪNULL
	warrior* bluewarrior;//����������ʿ��û����ΪNULL
	friend class head;
public:
	int successive_win;//ĳ������Ӯ�ĳ������췽Ϊ��������Ϊ��
	int winner;//Ӯ�� 1Ϊ�죬-1Ϊ����0û��Ӯ��
	city(){
		num = 0;
		flag = 0;
		life = 0;
		successive_win = 0;
		winner = 0;
		redwarrior = NULL;
		bluewarrior = NULL;
	}
	void init(int n){//��ʼ��
		num = n;
		flag = 0;
		life = 0;
		redwarrior = NULL;
		bluewarrior = NULL;
		winner = 0;
		successive_win = 0;
	}
	void set_red(warrior* p){
		redwarrior = p;
	}
	void set_blue(warrior* p){
		bluewarrior = p;
	}
	void set_flag(int c){
		flag = c;
	}
	void changelife(int n){
		life += n;
	}
	warrior* getred(){
		return redwarrior;
	}
	warrior* getblue(){
		return bluewarrior;
	}
	int getnum(){
		return num;
	}
	int getflag(){
		return flag;
	}
	void move(city* p);//��p�����е���ʿ�ƶ����ó�����
	void printmove();//��������ƶ�
	void lifetohead();//�������е�����Ԫ���͵�˾�
	void redwin();//�췽Ӯ�˺�Ӧ��������һϵ������
	void bluewin();
	void bekilled();//�������˺�����һϵ������
	void rewardtored();//˾�����ʤ����ʿ
	void rewardtoblue();
	void bomb();//�ڴ�ʹ��ը��
	void fight();//�ڴ�ս��
};
city pcity[30];//N������

class warrior{
protected:
	head * phead;//����˾�
	int kind;//����
	int num;//���
	int life;//����ֵ
	int attack;//������
	city* location;//���ڳ���
	int weapon[3];//�������ֱ���sword�Ĺ�������bomb����1��0����arrowʣ��ʹ�ô���
public:
	int pre_life;//ս��ǰ������ֵ����ʨ�ӱ�ɱ��ʱʹ��
	friend class city;
	friend class head;
	static int init_life[5];//��ʼ����ֵ
	static int init_attack[5];//��ʼ������
	static char*name[5];//��ʿ����
	warrior(head * phead, int kind, int num) :phead(phead), kind(kind), num(num),
		location(phead->color == 0 ? pcity : pcity + N + 1){
		life = init_life[kind];
		attack = init_attack[kind];
		pre_life = 0;
		//����Ϊ��������
		if (kind == 3 || kind == 4)
			memset(weapon, 0, sizeof(int)* 3);
		if (kind == 0 || kind == 2){
			weapon[0] = attack / 5 * (num % 3 == 0);
			weapon[1] = (num % 3 == 1);
			weapon[2] = 3 * (num % 3 == 2);
		}
		if (kind == 1){
			weapon[0] = attack / 5 * ((num + 2) % 3 != 0);
			weapon[1] = ((num + 2) % 3 != 1);
			weapon[2] = 3 * ((num + 2) % 3 != 2);//��num+2��%3��Ӧ��������Ϊ0
		}
	}
	virtual ~warrior(){}
	virtual void printproduce();//��ʿ����ʱ�����
	virtual void escape(){}//ʨ������
	virtual void win(){}//��ʿӮ�˺�ᷢ������
	virtual void even(){}//��ʿδ�ܻ�ʤʱӦ��������
	virtual void yell(){}//dragon����
	int getkind(){
		return kind;
	}
	int getlife(){
		return life;
	}
	int getnum(){
		return num;
	}
	int getbomb(){
		return weapon[1];
	}
	void set_pre_life(){
		pre_life = life;
	}
	void changelife(int dlife){
		life += dlife;
	}
	void arrow(warrior*p){//ʹ��arrow
		if (weapon[2] > 0){
			p->changelife(-R);
			--weapon[2];
			printf("%03d:%02d %s %s %d shot", chour, cmin, phead->cname[phead->color], name[kind], num);
			if (p->life <= 0)
				printf(" and killed %s %s %d", p->phead->cname[p->phead->color], name[p->kind], p->num);
			printf("\n");
		}
	}
	void disarm(warrior* p){//��е
		if (weapon[0] == 0)
			weapon[0] = p->weapon[0];
		if (weapon[1] == 0)
			weapon[1] = p->weapon[1];
		if (weapon[2] == 0)
			weapon[2] = p->weapon[2];
	}
	void weaponreport(){//��������
		printf("%03d:%02d %s %s %d has ", chour, cmin, phead->cname[phead->color], name[kind], num);
		int num_wea = int(weapon[0] != 0) + int(weapon[1] != 0) + int(weapon[2] != 0);
		if (num_wea == 0)
			printf("no weapon\n");
		else{
			if (weapon[2] != 0){
				--num_wea;
				printf("arrow(%d)", weapon[2]);
				if (num_wea)
					printf(",");
				else
					printf("\n");
			}
			if (weapon[1] != 0){
				--num_wea;
				printf("bomb");
				if (num_wea)
					printf(",");
				else
					printf("\n");
			}
			if (weapon[0] != 0){
				--num_wea;
				printf("sword(%d)", weapon[0]);
				if (num_wea)
					printf(",");
				else
					printf("\n");
			}
		}
	}
	void attackedby(warrior* p){//p������������ʿ
		printf("%03d:%02d %s %s %d attacked %s %s %d in city %d with %d elements and force %d\n",
			chour, cmin, p->phead->cname[p->phead->color], name[p->getkind()], p->getnum(),
			phead->cname[phead->color], name[kind], num, location->getnum(), p->life, p->attack);
		life -= p->attack;
		life -= p->weapon[0];
		p->weapon[0] = p->weapon[0] * 4 / 5;
	}
	void foughtbackby(warrior* p){//p��������ʿ
		printf("%03d:%02d %s %s %d fought back against %s %s %d in city %d\n",
			chour, cmin, p->phead->cname[p->phead->color], name[p->getkind()], p->getnum(),
			phead->cname[phead->color], name[kind], num, location->getnum());
		life -= p->attack / 2;
		life -= p->weapon[0];
		p->weapon[0] = p->weapon[0] * 4 / 5;
	}
};

class dragon :public warrior{
private:
	double morale;//ʿ��
public:
	dragon(head * phead, int num, double morale) :warrior(phead, 0, num), morale(morale){}
	void printproduce(){
		warrior::printproduce();
		printf("Its morale is %.2lf\n", morale);
	}
	virtual void yell(){//����
		int i = location->getnum();
		if (morale > 0.8 && ((pcity[i].getflag() == 1 || pcity[i].getflag() == 0 && i % 2 == 1) && phead->color == 0
			|| (pcity[i].getflag() == 2 || pcity[i].getflag() == 0 && i % 2 == 0) && phead->color == 1))
			printf("%03d:%02d %s dragon %d yelled in city %d\n", chour, cmin, phead->cname[phead->color],
			num, location->getnum());
	}
	virtual void win(){
		this->yell();
		morale += 0.2;
	}
	virtual void even(){
		morale -= 0.2;
	}
};
class ninja :public warrior{
public:
	ninja(head * phead, int num) :warrior(phead, 1, num){}
};
class iceman :public warrior{
public:
	iceman(head * phead, int num) :warrior(phead, 2, num){}
};
class lion :public warrior{
private:
	int loyalty;//�ҳ϶�
public:
	lion(head * phead, int num, int life_left) :warrior(phead, 3, num), loyalty(life_left){}
	void printproduce(){
		warrior::printproduce();
		printf("Its loyalty is %d\n", loyalty);
	}
	virtual void escape();//ʨ������
	virtual void even(){
		loyalty -= K;
	}
};
class wolf :public warrior{
public:
	wolf(head * phead, int num) :warrior(phead, 4, num){}
};


head::~head(){
	for (int i = 0; i < num; i++)
	if (pwarrior[i])
		delete pwarrior[i];
}
void head::produce(){
	int kind = ord[color][num % 5];//������������ʿ
	if (life < warrior::init_life[kind])
		return;
	life -= warrior::init_life[kind];
	num++;
	switch (kind){
	case 0:	pwarrior[num] = new dragon(this, num, double(life) / warrior::init_life[0]);
		pwarrior[num]->printproduce();
		break;
	case 1: pwarrior[num] = new ninja(this, num);
		pwarrior[num]->printproduce();
		break;
	case 2: pwarrior[num] = new iceman(this, num);
		pwarrior[num]->printproduce();
		break;
	case 3: pwarrior[num] = new lion(this, num, life);
		pwarrior[num]->printproduce();
		break;
	case 4: pwarrior[num] = new wolf(this, num);
		pwarrior[num]->printproduce();
		break;
	default:;
	}
	if (color == 0)//��˾���Ӧ�ĳ���������Ӧ���ã��Է�������ƶ�
		pcity[0].set_red(pwarrior[num]);
	else
		pcity[N + 1].set_blue(pwarrior[num]);
	return;
}
void city::move(city* p){//��p�Ƶ���ǰλ��
	if (num > p->num){//�����򶫣��ƶ�����ʿ
		if (p->redwarrior)
			p->redwarrior->location = this;//��ʿ�е�λ����ϢҪ�޸�
		redwarrior = p->redwarrior;
		p->redwarrior = NULL;
		if (redwarrior){
			if (num % 2 == 0 && redwarrior->kind == 2){//��iceman�����⴦��������������
				if (redwarrior->life > 9)
					redwarrior->life -= 9;
				else
					redwarrior->life = 1;
				redwarrior->attack += 20;
			}
			if (num == N + 1)
				bluehead.addenemy(redwarrior);//����˾�
		}
	}
	else{//�Զ��������ƶ�����ʿ
		if (p->bluewarrior)
			p->bluewarrior->location = this;
		bluewarrior = p->bluewarrior;
		p->bluewarrior = NULL;
		if (bluewarrior){
			if ((N + 1 - num) % 2 == 0 && bluewarrior->kind == 2){
				if (bluewarrior->life > 9)
					bluewarrior->life -= 9;
				else
					bluewarrior->life = 1;
				bluewarrior->attack += 20;
			}
			if (num == 0)
				redhead.addenemy(bluewarrior);
		}
	}
}
void city::printmove(){
	if (num == 0 && bluewarrior){
		printf("%03d:%02d blue %s %d reached red headquarter with %d elements and force %d\n", chour, cmin,
			warrior::name[bluewarrior->kind], bluewarrior->num, bluewarrior->life, bluewarrior->attack);
	}
	else if (num == N + 1 && redwarrior){
		printf("%03d:%02d red %s %d reached blue headquarter with %d elements and force %d\n", chour, cmin,
			warrior::name[redwarrior->kind], redwarrior->num, redwarrior->life, redwarrior->attack);
	}
	else if (num >= 1 && num <= N){
		if (redwarrior)
			printf("%03d:%02d red %s %d marched to city %d with %d elements and force %d\n", chour, cmin,
			warrior::name[redwarrior->kind], redwarrior->num, num, redwarrior->life, redwarrior->attack);
		if (bluewarrior)
			printf("%03d:%02d blue %s %d marched to city %d with %d elements and force %d\n", chour, cmin,
			warrior::name[bluewarrior->kind], bluewarrior->num, num, bluewarrior->life, bluewarrior->attack);
	}
}

void city::lifetohead(){//�����л�ʤ��ʿ����ֻ��һ�ˣ����ó�������Ԫ���ͻ�˾�
	if (bluewarrior && !redwarrior){
		bluehead.changelife(life);
		printf("%03d:%02d blue %s %d earned %d elements for his headquarter\n",
			chour, cmin, warrior::name[bluewarrior->getkind()], bluewarrior->getnum(), life);
		life = 0;
	}
	if (!bluewarrior && redwarrior){
		redhead.changelife(life);
		printf("%03d:%02d red %s %d earned %d elements for his headquarter\n",
			chour, cmin, warrior::name[redwarrior->getkind()], redwarrior->getnum(), life);
		life = 0;
	}
}
void city::redwin(){//�����к췽Ӯ
	winner = 1;
	if (successive_win >= 0)
		++successive_win;
	else
		successive_win = 1;
	redwarrior->win();
	if (redwarrior->getkind() == 4)//wolf��е
		redwarrior->disarm(bluewarrior);
	if (bluewarrior->getkind() == 3 && bluewarrior->getlife() <= 0)//ս��ʨ�ӽ�սǰ����ֵת�Ƶ�ʤ������
		redwarrior->changelife(bluewarrior->pre_life);
	bluewarrior = NULL;
	lifetohead();
	if (successive_win == 2 && flag != 1){//����
		printf("%03d:%02d red flag raised in city %d\n", chour, cmin, num);
		flag = 1;
		successive_win = 0;
	}
}
void city::bluewin(){//����Ӯ
	winner = -1;
	if (successive_win <= 0)
		--successive_win;
	else
		successive_win = -1;
	bluewarrior->win();
	if (bluewarrior->getkind() == 4)
		bluewarrior->disarm(redwarrior);
	if (redwarrior->getkind() == 3 && redwarrior->getlife() <= 0)
		bluewarrior->changelife(redwarrior->pre_life);
	redwarrior = NULL;
	lifetohead();
	if (successive_win == -2 && flag != 2){
		printf("%03d:%02d blue flag raised in city %d\n", chour, cmin, num);
		flag = 2;
		successive_win = 0;
	}
}
void city::bekilled(){
	if (redwarrior->getlife() <= 0)
		printf("%03d:%02d red %s %d was killed in city %d\n", chour, cmin,
		warrior::name[redwarrior->getkind()], redwarrior->num, num);
	if (bluewarrior->getlife() <= 0)
		printf("%03d:%02d blue %s %d was killed in city %d\n", chour, cmin,
		warrior::name[bluewarrior->getkind()], bluewarrior->num, num);
}
void city::rewardtored(){//˾��Գ����к���ʿ���н���
	if (redwarrior->phead->pre_life >= 8 && winner == 1){
		redwarrior->changelife(8);
		redwarrior->phead->changelife(-8);
	}
}
void city::rewardtoblue(){
	if (bluewarrior->phead->pre_life >= 8 && winner == -1){
		bluewarrior->changelife(8);
		bluewarrior->phead->changelife(-8);
	}
}
void city::bomb(){//������˫���жϼ�ʹ��bomb
	if (redwarrior->weapon[1] == 0 && bluewarrior->weapon[1] == 0)
		return;
	bool redkilled = false;
	bool bluekilled = false;
	//ģ��֮��ս�����̣�����Ԥ�⣨�᲻������
	if (flag == 1 || flag == 0 && num % 2 == 1){//�ֵ��췽��������
		if (bluewarrior->getlife() <= redwarrior->attack + redwarrior->weapon[0])
			bluekilled = true;
		else if (redwarrior->getlife() <= bluewarrior->attack / 2 + bluewarrior->weapon[0] && bluewarrior->getkind() != 1)
			redkilled = true;
	}
	else if (flag == 2 || flag == 0 && num % 2 == 0){//�ֵ�������������
		if (redwarrior->getlife() <= bluewarrior->attack + bluewarrior->weapon[0])
			redkilled = true;
		else if (bluewarrior->getlife() <= redwarrior->attack / 2 + redwarrior->weapon[0] && redwarrior->getkind() != 1)
			bluekilled = true;
	}
	//����Ԥ�⣬ʹ��bomb
	if (redwarrior->weapon[1] > 0 && redkilled){
		printf("%03d:%02d red %s %d used a bomb and killed blue %s %d\n", chour, cmin, warrior::name[redwarrior->getkind()],
			redwarrior->num, warrior::name[bluewarrior->getkind()], bluewarrior->num);
	}
	if (bluewarrior->weapon[1] > 0 && bluekilled){
		printf("%03d:%02d blue %s %d used a bomb and killed red %s %d\n", chour, cmin, warrior::name[bluewarrior->getkind()],
			bluewarrior->num, warrior::name[redwarrior->getkind()], redwarrior->num);
	}
	if (redwarrior->weapon[1] > 0 && redkilled || bluewarrior->weapon[1] > 0 && bluekilled){
		redwarrior = NULL;
		bluewarrior = NULL;
	}
}
void city::fight(){
	if (!redwarrior || !bluewarrior){
		winner = 0;
		if (redwarrior)
		if (redwarrior->getlife() <= 0)
			redwarrior = NULL;
		if (bluewarrior)
		if (bluewarrior->getlife() <= 0)
			bluewarrior = NULL;
		return;
	}
	if (redwarrior->getlife() <= 0 && bluewarrior->getlife() <= 0){
		redwarrior = NULL;
		bluewarrior = NULL;
	}
	else if (redwarrior->getlife() > 0 && bluewarrior->getlife() <= 0){
		bluewarrior->pre_life = 0;
		redwin();
	}
	else if (bluewarrior->getlife() > 0 && redwarrior->getlife() <= 0){
		redwarrior->pre_life = 0;
		bluewin();
	}
	else{
		redwarrior->set_pre_life();
		bluewarrior->set_pre_life();
		if (flag == 1 || flag == 0 && num % 2 == 1){//�췽��������
			bluewarrior->attackedby(redwarrior);
			if (bluewarrior->getlife() > 0 && bluewarrior->getkind() != 1)
				redwarrior->foughtbackby(bluewarrior);
			bekilled();//�������
			if (redwarrior->getlife() > 0 && bluewarrior->getlife() <= 0)//�췽Ӯ
				redwin();
			else if (bluewarrior->getlife() > 0 && redwarrior->getlife() <= 0)//����Ӯ
				bluewin();
			else{//ƽ��
				successive_win = 0;
				winner = 0;
				if (bluewarrior->getlife() > 0 && redwarrior->getlife() > 0){
					redwarrior->even();
					bluewarrior->even();
					if (redwarrior->getkind() == 0)//�����dragon�ж��Ƿ񻶺�
						redwarrior->yell();
				}
			}
		}
		else if (flag == 2 || flag == 0 && num % 2 == 0){//������������
			redwarrior->attackedby(bluewarrior);
			if (redwarrior->getlife() > 0 && redwarrior->getkind() != 1)
				bluewarrior->foughtbackby(redwarrior);
			bekilled();
			if (redwarrior->getlife() > 0 && bluewarrior->getlife() <= 0)//�췽Ӯ
				redwin();
			else if (bluewarrior->getlife() > 0 && redwarrior->getlife() <= 0)//����Ӯ
				bluewin();
			else{//ƽ��
				successive_win = 0;
				winner = 0;

				if (bluewarrior->getlife() > 0 && redwarrior->getlife() > 0){
					redwarrior->even();
					bluewarrior->even();
					if (bluewarrior->getkind() == 0)//�����dragon�ж��Ƿ񻶺�
						bluewarrior->yell();
				}
			}
		}
	}
}

void warrior::printproduce(){
	printf("%03d:%02d %s %s %d born\n", chour, cmin, phead->cname[phead->color], name[kind], num);
}
void lion::escape(){//ʨ������
	if (loyalty <= 0){
		if (phead->color == 0)
			location->set_red(NULL);
		else
			location->set_blue(NULL);
		printf("%03d:%02d %s lion %d ran away\n", chour, cmin, phead->cname[phead->color], num);
		phead->pwarrior[num] = NULL;
		phead = NULL;
	}
}

int warrior::init_life[5] = {};
int warrior::init_attack[5] = {};
char* warrior::name[5] = { "dragon", "ninja", "iceman", "lion", "wolf" };
char* head::cname[2] = { "red", "blue" };
int head::ord[2][5] = { { 2, 3, 4, 1, 0 }, { 3, 0, 1, 2, 4 } };

int main() {
	int t, k = 0;//t ������������
	cin >> t;
	while (t--){
		printf("Case %d:\n", ++k);
		cin >> M >> N >> R >> K >> T;
		for (int i = 0; i < 5; ++i)
			cin >> warrior::init_life[i];
		for (int i = 0; i < 5; ++i)
			cin >> warrior::init_attack[i];
		for (int i = 0; i<N + 2; i++)
			pcity[i].init(i);
		redhead.init(M);
		bluehead.init(M);
		chour = 0;

		while (chour * 60 + cmin <= T){
			cmin = 0;//0�֣���ʿ����
			if (chour * 60 + cmin > T)
				break;
			redhead.produce();
			bluehead.produce();

			cmin = 5;//5��ʨ������
			if (chour * 60 + cmin > T)
				break;
			for (int i = 0; i < N + 2; ++i){
				if (pcity[i].getred() && i != N + 1)
				if (pcity[i].getred()->getkind() == 3){
					pcity[i].getred()->escape();
				}
				if (pcity[i].getblue() && i != 0)
				if (pcity[i].getblue()->getkind() == 3){
					pcity[i].getblue()->escape();
				}
			}

			cmin = 10;//10�֣���ʿ�ƶ�
			if (chour * 60 + cmin > T)
				break;
			for (int i = N + 1; i >= 1; --i)//�ƶ�����ʿ
				pcity[i].move(pcity + i - 1);
			for (int i = 0; i <= N; ++i)//�ƶ�����ʿ
				pcity[i].move(pcity + i + 1);
			pcity[0].printmove();//���
			if (redhead.getenemy() >= 2){
				printf("%03d:%02d red headquarter was taken\n", chour, cmin);
			}
			for (int i = 1; i <= N; ++i)
				pcity[i].printmove();
			pcity[N + 1].printmove();
			if (bluehead.getenemy() >= 2){
				printf("%03d:%02d blue headquarter was taken\n", chour, cmin);
			}
			if (redhead.getenemy() >= 2 || bluehead.getenemy() >= 2)
				break;

			cmin = 20;//20�֣�ÿ����������ֵ��ʮ
			if (chour * 60 + cmin > T)
				break;
			for (int i = 1; i <= N; ++i)
				pcity[i].changelife(10);

			cmin = 30;//30�֣�������ֻ��һ����ʿ����ʿ������Ԫȡ���Ͻ�˾�
			if (chour * 60 + cmin > T)
				break;
			for (int i = 1; i <= N; ++i){
				pcity[i].lifetohead();
			}

			cmin = 35;//35�֣�ʹ��arrow
			if (chour * 60 + cmin > T)
				break;
			for (int i = 1; i <= N; ++i){
				if (i != N){//�췽����
					if (pcity[i].getred() && pcity[i + 1].getblue()){
						pcity[i].getred()->arrow(pcity[i + 1].getblue());
					}
				}
				if (i != 1){//����������
					if (pcity[i - 1].getred() && pcity[i].getblue()){
						pcity[i].getblue()->arrow(pcity[i - 1].getred());
					}
				}
			}

			cmin = 38;//38�֣�ʹ��bomb
			if (chour * 60 + cmin > T)
				break;
			for (int i = 1; i <= N; ++i){
				if (!pcity[i].getred() || !pcity[i].getblue())
					continue;
				if (pcity[i].getblue()->getlife() > 0 && pcity[i].getred()->getlife() > 0)
					pcity[i].bomb();
			}

			cmin = 40;//40�֣�ս��
			if (chour * 60 + cmin > T)
				break;
			redhead.set_pre_life();
			bluehead.set_pre_life();
			for (int i = 1; i <= N; ++i){
				pcity[i].fight();
			}
			for (int i = 1; i <= N; ++i)//�ɽ���Զ������ʤ�̵���ʿ,��Ч����˾��ջ�����Ԫ֮ǰ����
			if (pcity[i].getred())
				pcity[i].rewardtored();
			for (int i = N; i >= 1; --i)
			if (pcity[i].getblue())
				pcity[i].rewardtoblue();

			cmin = 50;//50�֣�˾���������Ԫ
			if (chour * 60 + cmin > T)
				break;
			redhead.reportlife();
			bluehead.reportlife();

			cmin = 55;//55�֣���ʿ��������
			if (chour * 60 + cmin > T)
				break;
			for (int i = 1; i <= N; ++i)//����ʿ����
			if (pcity[i].getred())
				pcity[i].getred()->weaponreport();
			if (bluehead.occupy)//˾��е�ҲҪ����
				bluehead.occupy->weaponreport();
			if (redhead.occupy)
				redhead.occupy->weaponreport();
			for (int i = 1; i <= N; ++i)//����ʿ����
			if (pcity[i].getblue())
				pcity[i].getblue()->weaponreport();

			chour++;
			cmin = 0;

		}
	}
	//system("pause");
	return 0;
}
