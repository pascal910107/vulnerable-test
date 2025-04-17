/**
 * @name Buffer Overflow Detection
 * @description 檢查可能透過 strcpy、sprintf 等導致緩衝區溢位的函式呼叫。
 * @kind problem
 * @id cpp/buffer-overflow-detection
 * @tags security
 */
import cpp

from CallExpr call, Function f
where
  f = call.getTarget().(Function) and
  f.getName() in ["strcpy", "sprintf"]
select call, "檢查可能的緩衝區溢位，請確認對輸入長度進行正確檢查。"
