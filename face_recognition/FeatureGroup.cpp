
#include "FeatureGroup.h"

//��ʼ��fg
FeatureGroup::FeatureGroup(int feat_dims, FaceRecognition* fr)
{
	this->feat_dims = feat_dims;
	this->fr = fr;
}
//�Ӵ��������ģ���ж�ȡ��������
FeatureGroup::FeatureGroup(string model_file, FaceRecognition* fr)
{	
	std::ifstream file;
	file.open(model_file);
	int size;
	float* new_feat;
	char* buffer = new char[1000];
	//��ģ�Ͷ�ȡ����
	file >> size;
	file >> this->feat_dims;
	for (int i = 0; i < size; i++)
	{
		Feature tmp;
		file.getline(buffer, 1000);
		while (buffer[0] == '\0' || buffer[0] == ' ')
		{
			file.getline(buffer, 1000);
		}
		//��ȡ����
		tmp.name = buffer;
		//��ȡid
		file.getline(buffer, 1000);
		tmp.id = buffer;
		//��ȡsno
		file.getline(buffer, 1000);
		tmp.sno = buffer;
		new_feat = new float[this->feat_dims];
		for (int j = 0; j < this->feat_dims; j++)
		{
			file >> new_feat[j];
		}
		tmp.data = new_feat;
		this->features.push_back(tmp);
	}
	file.close();
	this->fr = fr;
}
//��ȡ����ά��
int FeatureGroup::GetFeatureDims()
{
	return this->feat_dims;
}
//��vector�������������
bool FeatureGroup::AddFeature(float* feat, string name,string id,string sno)
{
	Feature tmp;
	float* new_feat = new float[this->feat_dims];
	//memcpy(new_feat, feat, sizeof(new_feat) * this->feat_dims);// ��仰ִ�������⣬�ĳ������ѭ��
	for (int i = 0; i < this->feat_dims; i++)
	{
		new_feat[i] = feat[i];
	}
	tmp.data = new_feat;
	tmp.name = name;
	tmp.id = id;
	tmp.sno = sno;
	this->features.push_back(tmp);
	return true;
}
//����ȡ����������浽����
bool FeatureGroup::SaveModel(string model_file)
{
	std::ofstream file;//������model��������
	string tmp_path = "database/tmp_feat.index";
	FaceRecognition fr_saveModel;
	FeatureGroup fg_saveModel(model_file, &fr_saveModel);
	
	file.open(tmp_path);
	file << int(this->features.size())+fg_saveModel.features.size() << std::endl; //���������ȡ�����ĸ���
	file << this->feat_dims << std::endl; //�����������ά��

	//�����ϰ汾��feat.index�ļ�д������
	for (int i = 0; i < int(fg_saveModel.features.size()); i++)
	{
		file << fg_saveModel.features[i].name << std::endl;
		file << fg_saveModel.features[i].id << std::endl;
		file << fg_saveModel.features[i].sno << std::endl;
		for (int j = 0; j < this->feat_dims; j++)
		{
			file << fg_saveModel.features[i].data[j] << " ";
		}
		file << std::endl;
	}


	//����д������
	for (int i = 0; i < int(this->features.size()); i++)
	{
		file << this->features[i].name << std::endl;
		file << this->features[i].id << std::endl;
		file << this->features[i].sno << std::endl;
		for (int j = 0; j < this->feat_dims; j++)
		{
			file << this->features[i].data[j] << " ";
		}
		file << std::endl;
	}
	file.close();
	remove(model_file.c_str());
	rename(tmp_path.c_str(),model_file.c_str());
	return true;
}

bool FeatureGroup::recognition(float* feat,Feature& f,float thershlod)
{
	std::cout << "Calculating Similarities..." << std::endl;
	float tmp,sim=0.0;

	for (int i = 0; i < this->features.size(); i++){
		tmp= this->fr->FeatureCompare(feat, this->features[i].data);
		if (tmp > sim){
			status = true;
			f.id = this->features[i].id;
			f.name = this->features[i].name;
			f.sno = this->features[i].sno;
			sim = tmp;
		}
	}
	return sim >= thershlod ? true : false;
} 
bool FeatureGroup::getStatus(){
	return this->status;
}

FeatureGroup::~FeatureGroup()  //��������ٻ����޸�
{
	for (int i = 0; i < int(this->features.size()); i++)
	{
		delete[](this->features[i].data);
	}

}