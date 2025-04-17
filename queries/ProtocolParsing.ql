/**
 * @name Protocol Parsing Error Risk Detection
 * @description 檢查協定解析函式中是否缺乏適當的錯誤處理機制。
 * @kind problem
 * @id cpp/protocol-parsing
 * @tags security
 */
import cpp

from CallExpr call, Function func
where
  func = call.getTarget().(Function) and
  func.getName().regexpMatch("^parse.*")
select call, "請確認協定解析函式中具備充分的錯誤處理。"
