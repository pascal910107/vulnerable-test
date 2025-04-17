/**
 * @name Null Pointer Dereference Detection
 * @description 檢查是否存在可能的空指標解引用。
 * @kind problem
 * @id cpp/null-pointer-dereference
 * @tags security
 */
import cpp

from Expr deref
where
  // 以下為簡單比對“*”運算子使用，實際情形需進行控制流檢查
  deref.toString().regexpMatch("^\*\\s*\\w+")
select deref, "檢查這裡是否可能解引用了空指標。"
