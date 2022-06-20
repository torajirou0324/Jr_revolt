#pragma once
#include <intsafe.h>
#include <set>
#include <vector>
#include <list>
#include <map>

namespace IKD
{

	template <class T>
	class CCell;
	///////////////////////////
	// 四分木登録オブジェクト
	///////////////////////////
	template <class T>
	class OBJECT_FOR_TREE
	{
	public:
		CCell<T>* m_pCell; // 登録空間
		T* m_pObject;      // 判定対象オブジェクト
		OBJECT_FOR_TREE<T>* m_pPre;  // 前のOBJECT_FOR_TREE構造体
		OBJECT_FOR_TREE<T>* m_pNext; // 次のOBJECT_FOR_TREE構造体
		int m_id;

		// コンストラクタ
		OBJECT_FOR_TREE(int id = 0)
		{
			m_id = id;
			m_pCell = nullptr;
			m_pObject = nullptr;		// 現在の判定対象のオブジェクト
			m_pPre = nullptr;			// 前回の判定対象のオブジェクト
			m_pNext = nullptr;			// 次のの判定対象のオブジェクト
		}

		// デストラクタ
		virtual ~OBJECT_FOR_TREE() {}

		// 自らリストから外れる
		bool Remove()
		{
			// 既に逸脱している時は処理終了
			if (!m_pCell) { return false; }

			// 自分を登録している空間に自身を通知
			if (!m_pCell->OnRemove(this))
			{
				return false;
			}

			// 逸脱処理
			// 前後のオブジェクトを結びつける
			if (m_pPre != 0)
			{
				m_pPre->m_pNext = m_pNext;
			}
			if (m_pNext != 0)
			{
				m_pNext->m_pPre = m_pPre;
			}
			m_pPre = 0;
			m_pNext = 0;
			m_pCell = nullptr;
			return true;
		}
	};

	///////////////////////////
	// 衝突リスト
	///////////////////////////
#define COLLISIONLIST_REALLOCSIZE 960
	template<class T>
	class CollisionList
	{
	public:
		// コンストラクタ
		CollisionList() : root_(0), pos_(0), mallocSize_(0)
		{
			root_ = (T**)malloc(0);
		}

		// デストラクタ
		~CollisionList()
		{
			reflesh();
		}

		size_t getSize()
		{
			return pos_;
		}
		T** getRootPtr()
		{
			return root_;
		}

		void resetPos()
		{
			pos_ = 0;
		}

		void wright(T* obj1, T* obj2)
		{
			if (pos_ >= mallocSize_)
			{
				root_ = (T**)realloc(root_, sizeof(T*) * (mallocSize_ + COLLISIONLIST_REALLOCSIZE));
				mallocSize_ += COLLISIONLIST_REALLOCSIZE;
			}
			root_[pos_++] = obj1;
			root_[pos_++] = obj2;
		}

		void reflesh()
		{
			if (root_)
			{
				free(root_);
			}
		}
	private:
		T** root_; // リストルートポインタ
		size_t pos_;
		size_t mallocSize_;
	};

	///////////////////////////
	// 線形４分木空間管理クラス
	///////////////////////////
#define CLINER4TREEMANAGER_MAXLEVEL 9
	template <class T>
	class CLiner4TreeManager
	{
	protected:
		unsigned int m_uiDim;
		CCell<T>** ppCellAraay; // 線形空間ポインタ配列
		unsigned int m_iPow[CLINER4TREEMANAGER_MAXLEVEL]; // べき乗数配列
		float m_fW;					// 領域のX軸幅
		float m_fH;					// 領域のY軸幅
		float m_fLeft;				// 領域の左側(X軸最小値)
		float m_fTop;				// 領域の上側(Y軸最小値)
		float m_fUnit_W;			// 最小レベル空間の幅単位
		float m_fUnit_H;			// 最小レベル空間の高単位
		DWORD m_dwCellNum;			// 空間の数
		unsigned int m_uiLevel;		// 最下位レベル
		CollisionList<T>m_ColList;	// 衝突リスト

	public:
		// コンストラクタ
		CLiner4TreeManager()
		{
			m_uiLevel = 0;
			m_fW = 0.0f;
			m_fH = 0.0f;
			m_fLeft = 0.0f;
			m_fTop = 0.0f;
			m_fUnit_W = 0.0f;
			m_fUnit_H = 0.0f;
			m_dwCellNum = 0;
			ppCellAraay = nullptr;
			m_uiDim = 0;

			// 各レベルでの空間数を算出
			int i;
			m_iPow[0] = 1;
			for (i = 1; i < CLINER4TREEMANAGER_MAXLEVEL + 1; i++)
			{
				m_iPow[i] = m_iPow[i - 1] * 4;
			}
		}

		// デストラクタ
		virtual ~CLiner4TreeManager(0
		{
			DWORD i;
			for (i = 0; i < m_dwCellNum; i++)
			{
				if (ppCellAraay[i] != nullptr)
				{
					delete ppCellAraay[i];
				}
			}
			delete[] ppCellAraay;
		}

		// 線形4分木配列を構築する
		bool Init(unsigned int Level, float left, float top, float right, float bottom)
		{
			// 設定最高レベル以上の空間は作れない
			if (Level >= CLINER4TREEMANAGER_MAXLEVEL)
			{
				return false;
			}

			// Level(0基点)の配列作成
			m_dwCellNum = (m_iPow[Level + 1] - 1) / 3;
			ppCellAraay = new CCell<T>*[m_dwCellNum];
			std::memset(ppCellAraay, sizeof(CCell<T>*) * m_dwCellNum);

			// 領域を登録
			m_fLeft = left;
			m_fTop = top;
			m_fW = right - left;
			m_fH = bottom - top;
			m_fUnit_W = m_fW / (1 << Level);
			m_fUnit_H = m_fH / (1 << Level);

			m_uiLevel = Level;
			return true;
		}

		// オブジェクトを登録する
		bool Regist(float left, float top, float right, float bottom, OBJECT_FOR_TREE<T>* pOFT)
		{
			// オブジェクトの境界範囲から登録モートン番号を算出
			DWORD Elem = GetMortonNumber(left, top, right, bottom);
			if (Elem < m_dwCellNum)
			{
				// 空間が無い場合は新規作成
				if (!ppCellAraay[Elem])
				{
					CreateNewCell(Elem);
					return ppCellAraay[Elem]->Push(pOFT);
				}
			}
			return false; // 登録失敗
		}

		// 衝突判定リストを作成する
		DWORD GetAllCollisionList(CollisionList<T>** colList)
		{
			// リスト(配列)は必ず初期化
			m_ColList.resetPos();

			// ルート空間の存在をチェック
			if (ppCellAraay[0] == 0)
			{
				return 0; // 空間が存在していない
			}

			// ルート空間を処理
			std::list<T*> ColStac;
			GetCollisionList(0, ColStac);

			*colList = &m_ColList;
			return (DWORD)m_ColList.getSize();
		}

	protected:
		// 空間内で衝突リストを作成する
		bool GetCollisionList(DWORD Elem, std::list<T*>& ColStac)
		{
			std::list<T*>::iteraor it;
			// ①空間内のオブジェクト同士の衝突リストを作成
			OBJECT_FOR_TREE<T>* pOFT1 = ppCellAraay[Elem]->GetFirstObj();
			while (pOFT1 != 0)
			{
				OBJECT_FOR_TREE<T>* pOFT2 = pOFT1->m_pNext;
				while (pOFT2 != 0)
				{
					m_ColList.wright(pOFT1->m_pObject, pOFT2->m_pObject);
					pOFT2 = pOFT2->m_pNext;
				}
				// ②衝突スタッフとの衝突リスト作成
				for (it = ColStac.begin(); it != ColStac.end(); it++)
				{
					m_ColList.wright(pOFT1->m_pObject, *it);
				}
				pOFT1 = pOFT1->m_pNext;
			}

			bool ChildFlag = false;
			// ③子空間に移動
			DWORD ObjNum = 0;
			DWORD i, NextElem;
			for (i = 0; i < 4; i++)
			{
				NextElem = Elem * 4 + 1 + i;
				if (NextElem < m_dwCellNum && ppCellAraay[Elem * 4 + 1 + i])
				{
					if (!ChildFlag)
					{
						// ④登録オブジェクトをスタックに追加
						pOFT1 = ppCellAraay[Elem]->GetFirstObj();
						while (pOFT1 != 0)
						{
							ColStac.push_back(pOFT1->m_pObject);
							ObjNum++;
							pOFT1 = pOFT1->m_pNext;
						}
					}
					ChildFlag = true;
					GetCollisionList(Elem * 4 + 1 + i, ColStac); // 子空間へ
				}
			}

			// ⑤スタックからオブジェクトを外す
			if (ChildFlag)
			{
				for (i = 0; i < ObjNum; i++)
				{
					ColStac.pop_back();
				}
			}

			return true;
		}

		// 空間を生成
		bool CreateNewCell(DWORD Elem)
		{
			// 引数の要素番号
			while (!ppCellAraay[Elem])
			{
				// 指定の要素番号に空間を新規作成
				ppCellAraay[Elem] = new CCell<T>;

				// 新空間にジャンプ
				Elem = (Elem - 1) >> 2;
				if (Elem >= m_dwCellNum) break;
			}
			return true;
		}

		// 座標から空間番号を算出
		DWORD GetMortonNumber(float left, float top, float right, float bottom)
		{
			// 最小レベルにおける各軸位置を算出
			DWORD LT;
		}

		// ビット分割関数
		DWORD BitSeparate32(WORD n)
		{
			n = (n | (n << 8)) & 0x00ff00ff;
			n = (n | (n << 4)) & 0x0f0f0f0f;
			n = (n | (n << 2)) & 0x33333333;
			return (n | (n << 1) & 0x55555555);
		}

		// 2Dモートン空間番号算出関数
		DWORD Get2DMortonNumber(WORD x, WORD y)
		{
			return (WORD)(BitSeparate32(x) | BitSeparate32(y));
		}

		// 座標→線形4分木要素番号変換関数
		DWORD GetPointElem(float pos_x, float pos_y)
		{
			return Get2DMortonNumber((WORD)((pos_x - m_fLeft) / m_fUnit_W), (WORD)(pos_y - m_fTop) / m_fUnit_H));
		}
	};

	///////////////////////////
	// 空間クラス
	///////////////////////////
	template <class T>
	class CCell
	{
	protected:
		OBJECT_FOR_TREE<T>* m_pLatest; // 最新OBJECT_FOR_TREE構造体へのポインタ
	public:
		// コンストラクタ
		CCell() : m_pLatest(nullptr)
		{
		}

		// デストラクタ
		virtual ~CCell()
		{
			if (m_pLatest != nullptr)
			{
				ResetLink(m_pLatest);
			}
		}

		// リンクを全リセットする
		void ResetLink(OBJECT_FOR_TREE<T>* pOFT)
		{
			if (pOFT == 0) { return false; } // 無効オブジェクトは登録しない
			if (pOFT->m_pCell == this) { return false; } // 2重登録チェック
			if (m_pLatest == 0)
			{
				m_pLatest = pOFT; // 空間に新規登録
			}
			else
			{
				// 最新オブジェクトを更新
				pOFT->m_pNext = m_pLatest;
				m_pLatest->m_pPre = pOFT;
				m_pLatest = pOFT;
			}
			pOFT->m_pCell = this; // 空間を登録
			return true;
		}

		// OFTをプッシュ
		bool Push(OBJECT_FOR_TREE<T>* pOFT)
		{
			if (pOFT == 0) { return false; } // 無効オブジェクトは登録しない
			if (pOFT->m_pCell == this) { return false; } // 2重登録チェック
			if (m_pLatest == 0)
			{
				m_pLatest = pOFT; // 空間に新規登録
			}
			else
			{
				// 最新オブジェクトを更新
				pOFT->m_pNext = m_pLatest;
				m_pLatest->m_pPre = pOFT;
				m_pLatest = pOFT;
			}
			pOFT->m_pCell = this; // 空間を登録
			return true;
		}

		// OBJECT_FOR_TREE構造体の先頭ポインタをゲットする関数
		OBJECT_FOR_TREE<T>* GetFirstObj()
		{
			return m_pLatest;
		}

		// 削除されるオブジェクトをチェック
		bool OnRemove(OBJECT_FOR_TREE<T>* pRemoveObj)
		{
			if (m_pLatest == pRemoveObj)
			{
				// 次のオブジェクトに挿れ替え
				if (m_pLatest != nullptr)
				{
					m_pLatest = m_pLatest->m_pNext;
				}
			}
			return true;
		}
	};
} // end namespace IKD[EOF]