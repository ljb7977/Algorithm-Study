#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>
#include <cstring>
#include <iostream>

#define NUM_OF_INSTRUCTION 20

using namespace std;

typedef struct instruction
{
	string name;
	char format;
	string op_funct;
} Inst;

typedef struct
{
	int type; //0 data, 1 label
	int order; //used for only label
	string code;
} Data_code;

typedef struct
{
	string inst;
	string code;
	int type; //0 code, 1 label, 2 not coded
	int order;
} Text_code;

const Inst inst[21] = {
	{"sll", 'R', "000000"},
	{"srl", 'R', "000010"},
	{"jr", 'R', "001000"},
	{"addu", 'R', "100001"},
	{"subu", 'R', "100011"},
	{"and", 'R', "100100"},
	{"or", 'R', "100101"},
	{"nor", 'R', "100111"},
	{"sltu", 'R', "101011"},
	{"j", 'J', "000010"},
	{"jal", 'J', "000011"},
	{"beq", 'I', "000100"},
	{"bne", 'I', "000101"},
	{"addiu", 'I', "001001"},
	{"sltiu", 'I', "001011"},
	{"andi", 'I', "001100"},
	{"ori", 'I', "001101"},
	{"lui", 'I', "001111"},
	{"lw", 'I', "100011"},
	{"sw", 'I', "101011"}
};

vector<Text_code> textcodes;
vector<Text_code>::iterator it;
vector<Data_code> datacodes;
vector<Data_code>::iterator d_it;

bool ishex(string number)
{
	return number.substr(0, 2) == "0x";
}

string dec_to_bin(int num, int len)
{
	string bin;
	int i;
	for(i=0;i<len;i++){
		bin = (char)((num&1)+'0') + bin;
		num>>=1;
	}
	return bin;
}

void ins_to_bin(string ins)
{
	int location=0;
	int offset;
	int inst_idx;
	int temp;
	Text_code t;
	string token, bin;
	string opcode="000000";
	string rt, rs, rd, shamt;
	rt = rs = rd = shamt = "00000";
	string imm, opfunct;

	char ins_char[32];

	if(ins[0] != '\t'){
		ins.pop_back();
		t.type = 1;
		t.code = ins;
		textcodes.push_back(t);
		return;
	}

	strncpy(ins_char, ins.c_str(), ins.length()+1);

	t.inst = ins;
	t.type = 0;
	token = strtok(ins_char, "\t");

	if (token == "la"){ //case la
		opcode = inst[17].op_funct;

		token = strtok(NULL, ", ");
		temp = stoi(token.substr(1));
		rt = dec_to_bin(temp, 5); //register number
		imm = dec_to_bin(0x1000, 16);

		t.code = opcode+"00000"+rt+imm;
		textcodes.push_back(t);

		token = strtok(NULL, ", ");
		for(d_it = datacodes.begin(); d_it != datacodes.end(); d_it++)
			if(d_it->type == 1)
				if(d_it->code == token)
					break;

		d_it++;
		location = d_it->order;
		//if (location%0x1000 == 0){
		if(location != 0){
			Text_code t;
			//ori
			opcode = inst[16].op_funct;
			rs = rt = dec_to_bin(temp, 5);
			imm = dec_to_bin(location*4, 16);
			t.code = opcode+rt+rs+imm;
			t.type = 0;
			textcodes.push_back(t);
		}
		return;
	}

	for(inst_idx=0; inst_idx<NUM_OF_INSTRUCTION; inst_idx++)
		if(token == inst[inst_idx].name)
			break;

	if(inst_idx == NUM_OF_INSTRUCTION){
		printf("undefined instruction!\n");
		return;
	}

	switch(inst[inst_idx].format){
		case 'R':
			opcode = "000000";
			rs = rt = rd = shamt = "00000";
			opfunct = inst[inst_idx].op_funct;
			if(inst_idx <= 1){
				token = strtok(NULL, ", ");
				temp = stoi(token.substr(1));
				rd = dec_to_bin(temp, 5);

				token = strtok(NULL, ", ");
				temp = stoi(token.substr(1));
				rt = dec_to_bin(temp, 5);

				token = strtok(NULL, ", ");
				temp = stoi(token);
				shamt = dec_to_bin(temp, 5);
			} else if (inst_idx == 2){
				token = strtok(NULL, ", ");
				temp = stoi(token.substr(1));
				rs = dec_to_bin(temp, 5);
			} else if (inst_idx >= 3){
				token = strtok(NULL, ", ");
				temp = stoi(token.substr(1));
				rd = dec_to_bin(temp, 5);

				token = strtok(NULL, ", ");
				temp = stoi(token.substr(1));
				rs = dec_to_bin(temp, 5);

				token = strtok(NULL, ", ");
				temp = stoi(token.substr(1));
				rt = dec_to_bin(temp, 5);
			}
			bin = opcode+rs+rt+rd+shamt+opfunct;
			break;

		case 'I':
			opcode = inst[inst_idx].op_funct;
			if(inst_idx <= 12){
				t.inst = ins;
				t.type = 2;
				textcodes.push_back(t);
				return;
			} else if (inst_idx <= 16){	//13 ~ 16
				token = strtok(NULL, ", ");
				temp = stoi(token.substr(1));
				rt = dec_to_bin(temp, 5);

				token = strtok(NULL, ", ");
				temp = stoi(token.substr(1));
				rs = dec_to_bin(temp, 5);

				token = strtok(NULL, ", ");
				temp = stoi(token, nullptr, 0);
				imm = dec_to_bin(temp, 16);
			} else if (inst_idx == 17){
				token = strtok(NULL, ", ");
				temp = stoi(token.substr(1));
				rt = dec_to_bin(temp, 5);

				token = strtok(NULL, ", ");
				temp = stoi(token, nullptr, 0);
				imm = dec_to_bin(temp, 16);
			} else if (inst_idx <= 19){
				token = strtok(NULL, ", ");
				temp = stoi(token.substr(1));
				rt = dec_to_bin(temp, 5);

				char *pt = strtok(NULL, ", ");

				if(ishex(token))
					sscanf(pt, "%x($%d)", &offset, &temp);
				else
					sscanf(pt, "%d($%d)", &offset, &temp);

				imm = dec_to_bin(offset, 16);
				rs = dec_to_bin(temp, 5);
			}
			bin = opcode+rs+rt+imm;
			break;
		case 'J':
			t.inst = ins;
			t.type = 2;
			textcodes.push_back(t);
			return;
	}

	t.code = bin;
	textcodes.push_back(t);
	return;
}

void data_to_bin(string data)
{
	Data_code d;
	string num;
	string label;
	int temp;
	char data_char[32];
	strncpy(data_char, data.c_str(), data.length());

	label = strtok(data_char, "\t"); //can be data label
	if(label != ".word"){//it is data label
		label.pop_back();
		Data_code l;
		l.type = 1;
		l.code = label;
		datacodes.push_back(l);
		num = strtok(NULL, "\t"); //.word
	}

	num = strtok(NULL, "\t"); //actual number
	temp = stoi(num, nullptr, 0);

	d.code = dec_to_bin(temp, 32);
	d.type = 0;
	datacodes.push_back(d);
}

void link_label(vector<Text_code>::iterator it)
{
	vector<Text_code>::iterator it2;
	char ins_char[32];
	string ins = it->inst;
	string token, opcode, rs, rt, imm, target;
	string bin;
	int inst_idx, distance, temp;

	strncpy(ins_char, ins.c_str(), ins.length()+1);

	token = strtok(ins_char, "\t");

	for(inst_idx=0; inst_idx<NUM_OF_INSTRUCTION; inst_idx++)
		if(token == inst[inst_idx].name)
			break;

	opcode = inst[inst_idx].op_funct;
	if(inst_idx == 11 || inst_idx == 12){	//beq, bne
		token = strtok(NULL, ", ");
		temp = stoi(token.substr(1));
		rs = dec_to_bin(temp, 5);

		token = strtok(NULL, ", ");
		temp = stoi(token.substr(1));
		rt = dec_to_bin(temp, 5);

		token = strtok(NULL, ", "); //token is label
		for(it2 = textcodes.begin(); it2 != textcodes.end(); it2++){
			if(it2->type != 1)
				continue;
			if(it2->code.compare(token) == 0)
				break;
		}
		it2++;

		distance = it2->order - it->order - 1;
		imm = dec_to_bin(distance, 16);

		bin = opcode + rs + rt + imm;
	} else if (inst_idx == 9 || inst_idx == 10){	//j, jal
		token = strtok(NULL, ", ");
		for(it2 = textcodes.begin(); it2 != textcodes.end(); it2++){
			if(it2->type != 1)
				continue;
			if(it2->code == token)
				break;
		}
		it2++;
		distance = (it2->order)*4 + 0x400000 >> 2;
		target = dec_to_bin(distance, 26);
		bin = opcode+target;
	}

	it->code = bin;
	it->type = 0;
}

int main(int argc, char* argv[]){
	string filename;
	freopen(argv[1], "r", stdin);
	filename = strtok(argv[1], ".");
	filename += ".o";
	freopen(filename.c_str(), "w", stdout);
	string ins;
	int i = 0;
	int data_size;
	int text_size;

	cin.ignore();
	getline(cin, ins, '\n'); //.data

	while(1){ //data section
		cin.ignore();
		getline(cin, ins, '\n');
		if(ins == "\t.text")
			break;
		data_to_bin(ins);
	}

	for(d_it = datacodes.begin(), i = 0; d_it != datacodes.end(); d_it++){
		if(d_it->type == 1)
			continue;
		d_it->order = i++;
	}

	cin.ignore();
	while(getline(cin, ins, '\n')){
		ins_to_bin(ins);
		cin.ignore();
	}

	for(it = textcodes.begin(), i =0; it != textcodes.end(); it++){
		if(it->type == 1)
			continue;
		it->order = i++;
	}

	for(it = textcodes.begin(); it != textcodes.end(); it++){
		if(it->type == 2){
			link_label(it);
		}
	}

	it = textcodes.end() - 1;
	text_size = (it->order+1)*4;

	printf("%s", dec_to_bin(text_size, 32).c_str());

	if(datacodes.size() == 0)
		data_size = 0;
	else {
		d_it = datacodes.end() - 1;
		data_size = (d_it->order+1)*4;
	}

	printf("%s", dec_to_bin(data_size, 32).c_str());

	for(it = textcodes.begin(); it != textcodes.end(); it++){
		if(it->type == 1)
			continue;
		printf("%s", it->code.c_str());
	}

	for(d_it = datacodes.begin(); d_it != datacodes.end(); d_it++){
		if(d_it->type == 1)
			continue;
		printf("%s", d_it->code.c_str());
	}

	return 0;
}
