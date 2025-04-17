/**
 * @name Unbounded Recursion Detection
 * @description 檢查函式中是否存在無終止條件的遞迴呼叫。
 * @kind problem
 * @id cpp/unbounded-recursion
 * @tags security
 */
import cpp

from FunctionDecl func, CallExpr call
where
  call.getCallee().(Function).getName() = func.getName() and
  not exists(call.getEnclosingStmt().(IfStmt))
select call, "請確認此遞迴呼叫具有適當的終止條件。"
