## vtable
```cpp
class Base {
 public:
  virtual ~Base();
  void Func();
  virtual void VFunc1();
  virtual void VFunc2();
}

class Sub : public Base {
 public:
  ~Sub();
  void Func();
  void VFunc1() override;
 private:
  int x;
};
```

クラスのメンバ関数を定義する際に`virtual`キーワードをつけることで，その関数は仮想関数ということになり，vtableに追加される．
一度vtableに追加されると，その子クラスでは特に`virtual`キーワードを付けなくてもその関数は仮想関数として扱われる．
したがってBaseクラスとその子クラスのSubのvtableは表↓のようになる．`virtual`キーワードで親クラスで付加していないBase::Funcは仮想関数にならない．したがって子クラスで同じ名前で同じ引数の関数を定義したとしても，それは親クラスの関数をオーバーライドすることにはならない．
よって，Sub::Funcにoverrideをつけるとエラーになる．

**Baseクラスのvtable**
| 関数名 | 値 |
| ---- | ---- |
| ~Base | Base::~Base |
| VFunc1 | Base::VFunc1 |
| VFunc2 | Base::VFunc2 |


**Subクラスのvtable**
| 関数名 | 値 |
| ---- | ---- |
| ~Sub | Sub::~Sub |
| VFunc1 | Sub::VFunc1 |
| VFunc2 | Base::VFunc2 |

仮想関数を1つ以上含むクラスのインスタンスの先頭にはvtableへのポインタが埋め込まれる．
即ちBaseクラスのインスタンスにはBase::vtableへのポインタが，SubクラスのインスタンスにはSub::vtableへのポインタが埋め込まれることになる．
埋め込まれたポインタはプログラマからは利用できないが，コンパイラが関数呼び出しの時に参照する．
次のようにSubのインスタンスをBaseとして扱う場合でも，vtable自体はSub::vtableが利用されるため，意図した関数が呼び出されることになる．

```cpp
Base* base_ptr = new Sub;
base_ptr->Func(); // vtable を使わない呼び出し． Base::Func が呼ばれる．
base_ptr->VFunc1(); // vtable　経由での呼び出し． Sub::VFunc1 が呼ばれる．
base_ptr->VFunc2(); // vtable 経由での呼び出し． Base::VFunc2 が呼ばれる．
delete base_ptr; // vtable 経由での呼び出し．　 Sub::~Sub が呼ばれる．
```
