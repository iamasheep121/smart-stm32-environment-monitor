#ifndef _ONENET_H_
#define _ONENET_H_

_Bool OneNet_DevLink(void);

void OneNet_SendData(void);

//void OneNET_Subscribe(void);
void OneNet_Subscribe(const char *topics[], unsigned char topic_cnt);//加强版可以自选订阅主题

//void OneNet_RevPro(unsigned char *cmd);
void OneNet_RevPro(unsigned char *cmd);
	
void OneNET_Publish(const char *topic, const char *msg);


#endif
