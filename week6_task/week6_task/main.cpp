/*
魔兽终极版
by 王腾霄  1300012819
*/

#include <iostream>
#include <string>
#include <string.h>
#include <stdio.h>
using namespace std;

/*
char* warrior::name[5] = {"dragon", "ninja", "iceman", "lion", "wolf"};
红方司令部按照 iceman、lion、wolf、ninja、dragon 的顺序制造武士。
蓝方司令部按照 lion、dragon、ninja、iceman、wolf 的顺序制造武士。
武器编号：0 sword, 1 bomb, 2 arrow。
*/

int chour = 0, cmin = 0;//时间：小时、分钟
int M, N, R, K, T;//M：司令部初始生命元数，N：城市个数， R:arrow攻击力
//K: lion忠诚度降低幅度，T：时间范围


class warrior;

class head{
private:
	int life, color, num;//生命值、颜色、武士数量
	int enemy;//进入司令部的敌人的数量
	warrior * pwarrior[1000];
	friend class warrior;
	friend class dragon;
	friend class ninja;
	friend class iceman;
	friend class lion;
	friend class wolf;
	friend class city;

public:
	int pre_life;//用于记录战斗后从各个城市收回生命元之前的生命值，在为武士进行奖励时使用该生命值
	warrior* occupy;//进入司令部的敌人。由于武士在到达对方司令部后仍要报告武器，所以将其存储于此。
	static char * cname[2];//颜色对应字符，red，blue
	static int ord[2][5];//产生武士的顺序
	head(int ccolor) :color(ccolor){
		life = 0;
		enemy = 0;
		num = 0;
		for (int i = 0; i < 1000; ++i)
			pwarrior[i] = NULL;
		pre_life = 0;
		occupy = NULL;
	}
	void init(int clife){//初始化函数
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
	//以上为返回相应的元素值
	void changelife(int n){
		life += n;
	}
	void set_pre_life(){
		pre_life = life;
	}
	void produce();//产生武士
	void reportlife(){
		printf("%03d:%02d %d elements in %s headquarter\n", chour, cmin, life, cname[color]);
	}
};
head redhead(0);//红司令部
head bluehead(1);//蓝司令部


class city{
private:
	int num;//城市编号
	int flag;//0：没有旗， 1：红旗，2：蓝旗
	int life;//城市的生命元
	warrior* redwarrior;//城市中红武士，没有则为NULL
	warrior* bluewarrior;//城市中蓝武士，没有则为NULL
	friend class head;
public:
	int successive_win;//某方连续赢的场数，红方为正，蓝方为负
	int winner;//赢家 1为红，-1为蓝，0没有赢家
	city(){
		num = 0;
		flag = 0;
		life = 0;
		successive_win = 0;
		winner = 0;
		redwarrior = NULL;
		bluewarrior = NULL;
	}
	void init(int n){//初始化
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
	void move(city* p);//将p城市中的武士移动到该城市中
	void printmove();//输出上述移动
	void lifetohead();//将城市中的生命元输送到司令部
	void redwin();//红方赢了后应当发生的一系列事情
	void bluewin();
	void bekilled();//有人死了后发生的一系列事情
	void rewardtored();//司令部奖励胜利武士
	void rewardtoblue();
	void bomb();//在此使用炸弹
	void fight();//在此战斗
};
city pcity[30];//N座城市

class warrior{
protected:
	head * phead;//所属司令部
	int kind;//种类
	int num;//编号
	int life;//生命值
	int attack;//攻击力
	city* location;//所在城市
	int weapon[3];//武器，分别是sword的攻击力，bomb（有1无0），arrow剩余使用次数
public:
	int pre_life;//战斗前的生命值，在狮子被杀死时使用
	friend class city;
	friend class head;
	static int init_life[5];//初始生命值
	static int init_attack[5];//初始攻击力
	static char*name[5];//武士名字
	warrior(head * phead, int kind, int num) :phead(phead), kind(kind), num(num),
		location(phead->color == 0 ? pcity : pcity + N + 1){
		life = init_life[kind];
		attack = init_attack[kind];
		pre_life = 0;
		//以下为分配武器
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
			weapon[2] = 3 * ((num + 2) % 3 != 2);//（num+2）%3对应的武器设为0
		}
	}
	virtual ~warrior(){}
	virtual void printproduce();//武士降生时的输出
	virtual void escape(){}//狮子逃亡
	virtual void win(){}//武士赢了后会发生的事
	virtual void even(){}//武士未能获胜时应发生的事
	virtual void yell(){}//dragon欢呼
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
	void arrow(warrior*p){//使用arrow
		if (weapon[2] > 0){
			p->changelife(-R);
			--weapon[2];
			printf("%03d:%02d %s %s %d shot", chour, cmin, phead->cname[phead->color], name[kind], num);
			if (p->life <= 0)
				printf(" and killed %s %s %d", p->phead->cname[p->phead->color], name[p->kind], p->num);
			printf("\n");
		}
	}
	void disarm(warrior* p){//缴械
		if (weapon[0] == 0)
			weapon[0] = p->weapon[0];
		if (weapon[1] == 0)
			weapon[1] = p->weapon[1];
		if (weapon[2] == 0)
			weapon[2] = p->weapon[2];
	}
	void weaponreport(){//报告武器
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
	void attackedby(warrior* p){//p主动攻击该武士
		printf("%03d:%02d %s %s %d attacked %s %s %d in city %d with %d elements and force %d\n",
			chour, cmin, p->phead->cname[p->phead->color], name[p->getkind()], p->getnum(),
			phead->cname[phead->color], name[kind], num, location->getnum(), p->life, p->attack);
		life -= p->attack;
		life -= p->weapon[0];
		p->weapon[0] = p->weapon[0] * 4 / 5;
	}
	void foughtbackby(warrior* p){//p还击该武士
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
	double morale;//士气
public:
	dragon(head * phead, int num, double morale) :warrior(phead, 0, num), morale(morale){}
	void printproduce(){
		warrior::printproduce();
		printf("Its morale is %.2lf\n", morale);
	}
	virtual void yell(){//欢呼
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
	int loyalty;//忠诚度
public:
	lion(head * phead, int num, int life_left) :warrior(phead, 3, num), loyalty(life_left){}
	void printproduce(){
		warrior::printproduce();
		printf("Its loyalty is %d\n", loyalty);
	}
	virtual void escape();//狮子逃跑
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
	int kind = ord[color][num % 5];//该生产哪种武士
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
	if (color == 0)//在司令部对应的城市中做相应设置，以方便进行移动
		pcity[0].set_red(pwarrior[num]);
	else
		pcity[N + 1].set_blue(pwarrior[num]);
	return;
}
void city::move(city* p){//从p移到当前位置
	if (num > p->num){//自西向东，移动红武士
		if (p->redwarrior)
			p->redwarrior->location = this;//武士中的位置信息要修改
		redwarrior = p->redwarrior;
		p->redwarrior = NULL;
		if (redwarrior){
			if (num % 2 == 0 && redwarrior->kind == 2){//对iceman的特殊处理——隔两步……
				if (redwarrior->life > 9)
					redwarrior->life -= 9;
				else
					redwarrior->life = 1;
				redwarrior->attack += 20;
			}
			if (num == N + 1)
				bluehead.addenemy(redwarrior);//进入司令部
		}
	}
	else{//自东向西，移动蓝武士
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

void city::lifetohead(){//城市中获胜武士（或只有一人）将该城市生命元输送回司令部
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
void city::redwin(){//城市中红方赢
	winner = 1;
	if (successive_win >= 0)
		++successive_win;
	else
		successive_win = 1;
	redwarrior->win();
	if (redwarrior->getkind() == 4)//wolf缴械
		redwarrior->disarm(bluewarrior);
	if (bluewarrior->getkind() == 3 && bluewarrior->getlife() <= 0)//战死狮子将战前生命值转移到胜者身上
		redwarrior->changelife(bluewarrior->pre_life);
	bluewarrior = NULL;
	lifetohead();
	if (successive_win == 2 && flag != 1){//升旗
		printf("%03d:%02d red flag raised in city %d\n", chour, cmin, num);
		flag = 1;
		successive_win = 0;
	}
}
void city::bluewin(){//蓝方赢
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
void city::rewardtored(){//司令部对城市中红武士进行奖励
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
void city::bomb(){//城市中双方判断及使用bomb
	if (redwarrior->weapon[1] == 0 && bluewarrior->weapon[1] == 0)
		return;
	bool redkilled = false;
	bool bluekilled = false;
	//模拟之后战斗过程，给出预测（会不会死）
	if (flag == 1 || flag == 0 && num % 2 == 1){//轮到红方主动出击
		if (bluewarrior->getlife() <= redwarrior->attack + redwarrior->weapon[0])
			bluekilled = true;
		else if (redwarrior->getlife() <= bluewarrior->attack / 2 + bluewarrior->weapon[0] && bluewarrior->getkind() != 1)
			redkilled = true;
	}
	else if (flag == 2 || flag == 0 && num % 2 == 0){//轮到蓝方主动出击
		if (redwarrior->getlife() <= bluewarrior->attack + bluewarrior->weapon[0])
			redkilled = true;
		else if (bluewarrior->getlife() <= redwarrior->attack / 2 + redwarrior->weapon[0] && redwarrior->getkind() != 1)
			bluekilled = true;
	}
	//根据预测，使用bomb
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
		if (flag == 1 || flag == 0 && num % 2 == 1){//红方主动出击
			bluewarrior->attackedby(redwarrior);
			if (bluewarrior->getlife() > 0 && bluewarrior->getkind() != 1)
				redwarrior->foughtbackby(bluewarrior);
			bekilled();//清点死人
			if (redwarrior->getlife() > 0 && bluewarrior->getlife() <= 0)//红方赢
				redwin();
			else if (bluewarrior->getlife() > 0 && redwarrior->getlife() <= 0)//蓝方赢
				bluewin();
			else{//平局
				successive_win = 0;
				winner = 0;
				if (bluewarrior->getlife() > 0 && redwarrior->getlife() > 0){
					redwarrior->even();
					bluewarrior->even();
					if (redwarrior->getkind() == 0)//如果是dragon判断是否欢呼
						redwarrior->yell();
				}
			}
		}
		else if (flag == 2 || flag == 0 && num % 2 == 0){//蓝方主动出击
			redwarrior->attackedby(bluewarrior);
			if (redwarrior->getlife() > 0 && redwarrior->getkind() != 1)
				bluewarrior->foughtbackby(redwarrior);
			bekilled();
			if (redwarrior->getlife() > 0 && bluewarrior->getlife() <= 0)//红方赢
				redwin();
			else if (bluewarrior->getlife() > 0 && redwarrior->getlife() <= 0)//蓝方赢
				bluewin();
			else{//平局
				successive_win = 0;
				winner = 0;

				if (bluewarrior->getlife() > 0 && redwarrior->getlife() > 0){
					redwarrior->even();
					bluewarrior->even();
					if (bluewarrior->getkind() == 0)//如果是dragon判断是否欢呼
						bluewarrior->yell();
				}
			}
		}
	}
}

void warrior::printproduce(){
	printf("%03d:%02d %s %s %d born\n", chour, cmin, phead->cname[phead->color], name[kind], num);
}
void lion::escape(){//狮子逃跑
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
	int t, k = 0;//t 测试数据组数
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
			cmin = 0;//0分，武士降生
			if (chour * 60 + cmin > T)
				break;
			redhead.produce();
			bluehead.produce();

			cmin = 5;//5分狮子逃走
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

			cmin = 10;//10分，武士移动
			if (chour * 60 + cmin > T)
				break;
			for (int i = N + 1; i >= 1; --i)//移动红武士
				pcity[i].move(pcity + i - 1);
			for (int i = 0; i <= N; ++i)//移动蓝武士
				pcity[i].move(pcity + i + 1);
			pcity[0].printmove();//输出
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

			cmin = 20;//20分，每座城市生命值加十
			if (chour * 60 + cmin > T)
				break;
			for (int i = 1; i <= N; ++i)
				pcity[i].changelife(10);

			cmin = 30;//30分，城市中只有一个武士，武士将生命元取走上交司令部
			if (chour * 60 + cmin > T)
				break;
			for (int i = 1; i <= N; ++i){
				pcity[i].lifetohead();
			}

			cmin = 35;//35分，使用arrow
			if (chour * 60 + cmin > T)
				break;
			for (int i = 1; i <= N; ++i){
				if (i != N){//红方向东射
					if (pcity[i].getred() && pcity[i + 1].getblue()){
						pcity[i].getred()->arrow(pcity[i + 1].getblue());
					}
				}
				if (i != 1){//蓝方向西射
					if (pcity[i - 1].getred() && pcity[i].getblue()){
						pcity[i].getblue()->arrow(pcity[i - 1].getred());
					}
				}
			}

			cmin = 38;//38分，使用bomb
			if (chour * 60 + cmin > T)
				break;
			for (int i = 1; i <= N; ++i){
				if (!pcity[i].getred() || !pcity[i].getblue())
					continue;
				if (pcity[i].getblue()->getlife() > 0 && pcity[i].getred()->getlife() > 0)
					pcity[i].bomb();
			}

			cmin = 40;//40分，战斗
			if (chour * 60 + cmin > T)
				break;
			redhead.set_pre_life();
			bluehead.set_pre_life();
			for (int i = 1; i <= N; ++i){
				pcity[i].fight();
			}
			for (int i = 1; i <= N; ++i)//由近到远奖励打胜仗的武士,等效于在司令部收回生命元之前奖励
			if (pcity[i].getred())
				pcity[i].rewardtored();
			for (int i = N; i >= 1; --i)
			if (pcity[i].getblue())
				pcity[i].rewardtoblue();

			cmin = 50;//50分，司令部报告生命元
			if (chour * 60 + cmin > T)
				break;
			redhead.reportlife();
			bluehead.reportlife();

			cmin = 55;//55分，武士报告武器
			if (chour * 60 + cmin > T)
				break;
			for (int i = 1; i <= N; ++i)//红武士报告
			if (pcity[i].getred())
				pcity[i].getred()->weaponreport();
			if (bluehead.occupy)//司令部中的也要报告
				bluehead.occupy->weaponreport();
			if (redhead.occupy)
				redhead.occupy->weaponreport();
			for (int i = 1; i <= N; ++i)//蓝武士报告
			if (pcity[i].getblue())
				pcity[i].getblue()->weaponreport();

			chour++;
			cmin = 0;

		}
	}
	//system("pause");
	return 0;
}
