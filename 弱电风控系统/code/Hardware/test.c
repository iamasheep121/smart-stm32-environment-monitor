#include "stm32f10x.h"
#include <stdio.h>
#include "OLED.h"
//// 任务1：补全这个函数
//void greet() {
//	printf("你好\r\n");
//    // 在这里打印"你好！"
//}

//// 任务2：补全这个函数  
//void bye() {
//	printf("再见\r\n");
//    // 在这里打印"再见！"
//}

//#include <stdio.h>

//// 任务1：定义回调函数类型Callback
//// 提示：typedef void (*Callback)();
//typedef void (*callback)(void);


//// 任务2：完成这个函数
//void process_data( callback Callback) {
//	
//    printf("开始处理数据...\n");
//    
//    // 任务3：模拟数据处理（延时）
//    for(int i = 0; i < 3; i++) {
//        printf("处理中%d/3\n", i+1);
//    }
//    
//    printf("数据处理完成！\n");
//    
//    // 任务4：如果有回调函数，就执行它
//    if(Callback != NULL)
//	{
//		Callback();
//	}
//}

//// 具体的回调函数
//void on_success() {
//    printf("? 数据处理成功回调被执行！\n");
//}

//void on_error() {
//    printf("? 数据处理错误回调被执行！\n");
//}

////int main() {
////		Serial_Init();
////    // 任务5：测试不同的回调函数
////    printf("测试1：成功回调\n");
////    process_data(on_success);
////    
////    printf("\n测试2：错误回调\n");
////    process_data(on_error);
////    
////    printf("\n测试3：无回调\n");
////    process_data(NULL);
////    
////    return 0;
////}


////int main() {
////
////    // 任务3：声明一个函数指针func_ptr
////    // 提示：void (*func_ptr)();
////	void (*func_ptr)();
////    
////    // 任务4：让func_ptr指向greet函数并调用
////    func_ptr = greet;
////	func_ptr();
////    // 任务5：让func_ptr指向bye函数并调用
////    func_ptr = bye;
////	func_ptr();
////    return 0;
////}


