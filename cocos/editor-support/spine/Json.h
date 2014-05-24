/*
 Copyright (c) 2009 Dave Gamble
 
 Permission is hereby granted, dispose of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

/* Esoteric Software: Removed everything except parsing, shorter method names, more get methods, double to float, formatted. */
/* Esoteric Software: 移除除了解析，简短的名字，get方法, 双精度浮点转换为单精度浮点数（double to float）, 格式化之外的所有方法. */

#ifndef SPINE_JSON_H_
#define SPINE_JSON_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Json 类型: */
#define Json_False 0
#define Json_True 1
#define Json_NULL 2
#define Json_Number 3
#define Json_String 4
#define Json_Array 5
#define Json_Object 6

/* Json结构: */
typedef struct Json {
	struct Json* next;
	struct Json* prev; /* next/prev 允许你遍历整个数组/对象. 你还可以使用getSize/getItem达到相同目地 */
	struct Json* child; /* 数组或者对象可能具有一个child指针， child指向他们的所有子项的链表. */

	int type; /* json数据的类型，使用上面定义的Json类型的值. */
	int size; /* 子节点数量. */

	const char* valueString; /* 结构的字符串值, 要求 type==Json_String 才有意义 */
	int valueInt; /* 结构的整型值, 要求 type==Json_Number 才有意义 */
	float valueFloat; /* 结构的浮点值, 要求 type==Json_Number 才有意义 */

	const char* name; /* 结构的名字字符串, 结构式object的子节点子项if this item is the child of, or is in the list of subitems of an object. */
} Json;

/* 提供JSON数据块, 返回一个Json对象用于后序操作，当操作完成后调用Json_dispose销毁对象. */
Json* Json_create (const char* value);

/* 删除Json结构体和他的所有子节点. */
void Json_dispose (Json* json);

/* 获取Json的Object对象"string"项. 不区分大小写. */
Json* Json_getItem (Json* json, const char* string);
const char* Json_getString (Json* json, const char* name, const char* defaultValue);
float Json_getFloat (Json* json, const char* name, float defaultValue);
int Json_getInt (Json* json, const char* name, int defaultValue);

/* 如果解析失败，返回解析错误信息的字符串, 你可能要向后查看几个字符来搞清楚它的含义。当Json_create()返回0时被设置. Json_create()成功是返回0 */
const char* Json_getError (void);

#ifdef __cplusplus
}
#endif

#endif /* SPINE_JSON_H_ */
