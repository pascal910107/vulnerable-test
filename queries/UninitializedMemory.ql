/**
 * @name Uninitialized Memory Usage
 * @description 檢查宣告變數後未初始化就被使用的情況。
 * @kind problem
 * @id cpp/uninitialized-memory
 * @tags security
 */
import cpp

from VarDecl var, VariableAccess access
where
  var.getInitializer() = null and
  access.getDecl() = var and
  // 此處以存取作為使用的檢查，實際上可能需要更細部的資料流分析
  access.getAccessType() = AccessWrite
select access, "變數未初始化即被使用，請檢查是否需要初始化。"
