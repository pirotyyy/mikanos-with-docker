## ポインタとアセンブリ言語

```cpp
void foo() {
  int i = 42;
  int* p = &i;
  int r1 = *p;
  *p = 1;
  int r2 = i;
  uintptr_t addr = reinterpret_cast<uintptr_t>(p);
  int* q = reinterpret_cast<int*>(addr);
}
```

上記のC++プログラムをClangでコンパイルすると以下のようになる．まずは関数の前半部分．
```
_Z3foov:
    push  rbp
    mov   rbp, rsp

    ; int i = 42;
    mov   dword ptr [rbp - 4], 42
```
「_Z3foov」は，関数fooのアセンブリ言語の世界における名前．
C++の名前修飾により，このように異なる名前に変換される．

2行目，3行目は関数の入り口における典型的な処理である．
2行目のpush命令は，RSPレジスタの値を8だけ減らしてからRSPレジスタが指すメモリ領域に指定された値を書き込む．
即ち，RBPレジスタの値がスタックの末尾に保存される．
3行目のmov命令は右から左方向への値のコピーである．RSPの値は一般にどんどん変化するため，あとで基準点として使えるように，ある瞬間の値をコピーしておく．

後半部分は以下に記載．
lea (Load Effective Address)は，実際のメモリアクセスは行わずにメモリアドレスを計算した結果をレジスタに書き込む命令である．

```
; int* p = &i;
lea   rax, [rbp - 4]
mov   qword ptr [rbp - 16], rax

; int r1 = *p;
mov   rax, qword ptr [rbp - 16]
mov   ecx, dword ptr [rax]
mov   dword ptr [rbp - 20], ecx

; *p = 1;
mov   rax, qword ptr [rbp - 16]
mov   dword ptr [rax], 1

; int r2 = i;
mov   ecx, dword ptr [rbp - 4]
mov   dword ptr [rbp - 24], ecx

; uintptr_t addr = reinterpret_cast<uintptr_t>(p);
mov   rax, qword ptr [rbp - 16]
mov   qword ptr [rbp - 32], rax

; int* q = reinterpret_cast<int*>(addr);
mov   rax, qword ptr [rbp - 32]
mov   qword ptr [rbp - 40], rax

pop rbp
ret
```