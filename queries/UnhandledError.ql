/**
 * @name Unhandled Error Detection
 * @description 檢查檔案操作（例如 fopen）後是否有錯誤處理。
 * @kind problem
 * @id cpp/unhandled-error
 * @tags security
 */
import cpp

from CallExpr call
where
  call.getTarget().(Function).getName() = "fopen" and
  not exists(call.getEnclosingStmt().(IfStmt))
select call, "請確認 fopen 呼叫之後有進行錯誤檢查。"
