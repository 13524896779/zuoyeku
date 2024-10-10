#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000 // 定义最大文本长度
#define MAX_OPS 100   // 定义最大操作数

// 文本编辑器结构体，用于存储文本内容
typedef struct {
    char* text;       // 存储文本的数组
    int len;          // 当前文本长度
    int capacity;     // 文本的最大容量
} TextEditor;

// 撤销和重做操作的结构体，用于记录操作信息
typedef struct {
    int position;     // 操作的位置
    char character;   // 操作的字符
} UndoRedoOp;

// 栈结构体，用于实现撤销和重做功能
typedef struct {
    UndoRedoOp ops[MAX_OPS]; // 存储操作的数组
    int top;                // 栈顶位置
} Stack;

// 初始化栈
void initStack(Stack* s) {
    s->top = -1;
}

// 判断栈是否已满
int isFull(Stack* s) {
    return s->top == MAX_OPS - 1;
}

// 判断栈是否为空
int isEmpty(Stack* s) {
    return s->top == -1;
}

// 向栈中压入一个操作
void push(Stack* s, UndoRedoOp op) {
    if (isFull(s)) {
        printf("栈已满\n");
        return;
    }
    s->ops[++s->top] = op;
}

// 从栈中弹出一个操作
UndoRedoOp pop(Stack* s) {
    if (isEmpty(s)) {
        UndoRedoOp op = { -1, '\0' };
        return op;
    }
    return s->ops[s->top--];
}

// 初始化文本编辑器
void initTextEditor(TextEditor* editor) {
    editor->text = (char*)malloc(MAX_SIZE * sizeof(char));
    editor->len = 0;
    editor->capacity = MAX_SIZE;
}

// 释放文本编辑器资源
void freeTextEditor(TextEditor* editor) {
    free(editor->text);
}

// 在指定位置插入字符
void insertChar(TextEditor* editor, int position, char character) {
    if (editor->len >= editor->capacity) {
        printf("文本编辑器已满\n");
        return;
    }
    memmove(editor->text + position + 1, editor->text + position, editor->len - position + 1);
    editor->text[position] = character;
    editor->len++;
}

// 删除指定位置的字符
void deleteChar(TextEditor* editor, int position) {
    if (position < 0 || position >= editor->len) {
        printf("无效的位置\n");
        return;
    }
    memmove(editor->text + position, editor->text + position + 1, editor->len - position);
    editor->len--;
}

// 撤销最近一次操作
void undo(TextEditor* editor, Stack* undoStack, Stack* redoStack) {
    if (isEmpty(undoStack)) {
        printf("没有操作可以撤销\n");
        return;
    }
    UndoRedoOp op = pop(undoStack);
    push(redoStack, op);
    if (op.position == -1) {
        insertChar(editor, op.position, op.character);
    }
    else {
        deleteChar(editor, op.position);
    }
}

// 重做最近一次撤销的操作
void redo(TextEditor* editor, Stack* undoStack, Stack* redoStack) {
    if (isEmpty(redoStack)) {
        printf("没有操作可以重做\n");
        return;
    }
    UndoRedoOp op = pop(redoStack);
    push(undoStack, op);
    if (op.position == -1) {
        deleteChar(editor, op.position);
    }
    else {
        insertChar(editor, op.position, op.character);
    }
}

// 记录操作到撤销栈
void recordOperation(Stack* undoStack, int position, char character, int type) {
    UndoRedoOp op;
    op.position = position;
    op.character = character;
    push(undoStack, op);
}

// 打印当前文本内容
void printText(TextEditor* editor) {
    printf("当前文本: %s\n", editor->text);
}

// 保存文本到文件
void saveText(TextEditor* editor, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("无法打开文件进行写入\n");
        return;
    }
    fwrite(editor->text, sizeof(char), editor->len, file);
    fclose(file);
    printf("文本已保存到文件 %s\n", filename);
}

// 从文件加载文本
void loadText(TextEditor* editor, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("无法打开文件进行读取\n");
        return;
    }
    editor->len = fread(editor->text, sizeof(char), editor->capacity, file);
    fclose(file);
    printf("文本已从文件 %s 加载\n", filename);
}

// 打印操作菜单
void printMenu() {
    printf("文本编辑器菜单：\n");
    printf("1. 插入字符\n");
    printf("2. 删除字符\n");
    printf("3. 撤销\n");
    printf("4. 重做\n");
    printf("5. 打印文本\n");
    printf("6. 保存文本到文件\n");
    printf("7. 从文件加载文本\n");
    printf("8. 退出\n");
    printf("请输入你的选择：");
}

// 主函数，用于测试文本编辑器功能
int main() {
    TextEditor editor;
    initTextEditor(&editor);
    Stack undoStack, redoStack;
    initStack(&undoStack);
    initStack(&redoStack);

    char buffer[MAX_SIZE];
    int choice, position;
    char character;
    while (1) {
        printMenu();
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("读取输入失败\n");
            continue;
        }
        if (sscanf(buffer, "%d", &choice) != 1) {
            printf("无效的输入\n");
            continue;
        }
        switch (choice) {
        case 1:
            printf("请输入要插入的位置和字符：");
            if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
                printf("读取输入失败\n");
                continue;
            }
            if (sscanf(buffer, "%d %c", &position, &character) != 2) {
                printf("无效的输入\n");
                continue;
            }
            insertChar(&editor, position, character);
            recordOperation(&undoStack, position, character, 1);
            printText(&editor);
            break;
        case 2:
            printf("请输入要删除的位置：");
            if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
                printf("读取输入失败\n");
                continue;
            }
            if (sscanf(buffer, "%d", &position) != 1) {
                printf("无效的输入\n");
                continue;
            }
            character = editor.text[position];
            deleteChar(&editor, position);
            recordOperation(&undoStack, position, character, 0);
            printText(&editor);
            break;
        case 3:
            undo(&editor, &undoStack, &redoStack);
            printText(&editor);
            break;
        case 4:
            redo(&editor, &undoStack, &redoStack);
            printText(&editor);
            break;
        case 5:
            printText(&editor);
            break;
        case 6:
            printf("请输入要保存的文件名：");
            fgets(buffer, sizeof(buffer), stdin);
            saveText(&editor, buffer);
            break;
        case 7:
            printf("请输入要加载的文件名：");
            fgets(buffer, sizeof(buffer), stdin);
            loadText(&editor, buffer);
            printText(&editor);
            break;
        case 8:
            freeTextEditor(&editor);
            return 0;
        default:
            printf("无效的选择\n");
        }
    }
}