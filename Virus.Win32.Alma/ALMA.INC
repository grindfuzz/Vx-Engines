;������
Err_UNC       equ 1 ; ����������� �������

;�������� �������
ComandInfo struc
     cOpCod    dd ?         ;00    �����
     cAdr      db 6 DUP (?) ;02    ��������
     cData     db 6 DUP (?) ;08    ����
     cLen      db ?         ;0E    ����� ���������� (��� ���� � ��������)
     cALen     db ?         ;0F    ����� ��������

     cDLen     db ?         ;10    ����� ����
     cModRM    db ?         ;11    ModRM (1-���� 0-���)
     cMod      db ?         ;12    Mod   (xx000000b)
     cRM       db ?         ;13    RM    (00000xxxb)
     cReg      db ?         ;14    Reg   (00xxx000b)
     cSIB      db ?         ;15    SIB   (1-���� 0-���)
     cSibSS    db ?         ;16    Scale (xx000000b)
     cSibIndex db ?         ;17    Index (00xxx000b)
     cSibBase  db ?         ;18    Base  (00000xxxb)
     cFlg_0F   db ?         ;xx    ���� ������� 0Fh    (1-���� 0-���)
     ;������ �������� ������������� ��� ���������
     cFlg_66   db ?         ;19    ���� ������� 66h    (1-���� 0-���)
     cFlg_67   db ?         ;1A    ���� ������� 67h    (1-���� 0-���)
     cFlg_F0   db ?         ;1B    ���� ������� F0h    (1-���� 0-���)
     cFlg_Seg  db ?         ;1C    �������� ��������   (0-���)
     cFlg_Rep  db ?         ;1D    �������� ���������� (0-���)
     cDflag    db ?         ;1E    ���� �����������
     cWflag    db ?         ;1F    ���� �������

     cSflag    db ?         ;20    ���� ��������� ����������
     cFloat    db ?         ;21    ������� ����� (00xxxyyyb)
     cType     db ?         ;22    ��� �������
ends
ComandInfoLen  equ cType-cOpCod+1

; ��c����������� �������:

; ��� ModRM � ����
command01    = 1;type 1h  -  push/pop reg
command02    = 1;type 2h  -  push/pop seg (es,cs,ds,ss)
command03    = 1;type 3h  -  pusha/popa
command04    = 1;type 4h  -  pushf/popf
command05    = 1;type 5h  -  xchg a,reg
command06    = 1;type 6h  -  CLx/STx
command07    = 1;type 7h  -  inc/dec reg
command08    = 1;type 8h  -  cbw/cwd
command09    = 1;type 9h  -  ��������� ������� (movs, lods, ...)
command0a    = 1;type ah  -  xlat
command0c    = 1;type ch  -  ret
command0d    = 1;type dh  -  nop
command0e    = 1;type eh  -  int 3
command0f    = 1;type fh  -  ��������� ����/����� � ����������� ������, ��������� DX
command10    = 1;type 10h  -  cmc - �������� CF
command11    = 1;type 11h  -  LAHF/SAHF
command12    = 1;type 12h  -  DAA,DAS -(������),AAA,AAS(��������) ���  AL
command14    = 1;type 14h  -  hlt
command15    = 1;type 15h  -  wait
command16    = 1;type 16h  -  salc-���������� AL � -CF


;�������� �������� ��������
;������� 66h
;������� 67h

; ��� ModRM, ���� ����
command21    = 1;type 21h  -  mov reg,NOP
command22    = 1;type 22h  -  mov a,mem (d=0|1)
command23    = 1;type 23h  -  push NOP
command24    = 1;type 24h  -  �����. � �����. �������� ���� � �������������
command25    = 1;type 25h  -  test a,NOP
command26    = 1;type 26h  -  call/jmp � ������ ����������
command27    = 1;type 27h  -  ����������������:)
command28    = 1;type 28h  -  Jxx short
command29    = 1;type 29h  -  LOOPxx/JCXZ
command2a    = 0;type 2ah  -  ����������, ��������� �������� � ��������; ���������� :)
command2b    = 1;type 2bh  -  ����/����� ����� �����������
command2c    = 1;type 2ch  -  ��������� �� ��������� ������ �� DIV, ����� MUL (AX-������ �����)
command2d    = 1;type 2dh  -  ����������, ��������� �������� � ��������
command2e    = 1;type 2eh  -  RET imm8
command2F    = 1;type 2Fh  -  call far NOP

; ���� ModRM � ��� ����
command41    = 1   ;type 41h  -  mov reg/mem,reg (d=0|1)
command42    = 1   ;type 42h  -  mov sr,reg/mem (d=0|1)
command43    = 1   ;type 43h  -  push mem
command44    = 1   ;type 44h  -  pop mem
command45    = 1   ;type 45h  -  call/jmp � ����. �����. ����� reg/mem
command46    = 1   ;type 46h  -  test/xchg reg/mem,reg
command47    = 1   ;type 47h  -  lea reg,addr
command48    = 1   ;type 48h  -  lds/les
command49    = 1   ;type 49h  -  �����. � �����. �������� reg,reg/mem
command4a    = 1   ;type 4ah  -  inc/dec reg/mem
command4b    = 1   ;type 4bh  -  neg reg/mem
command4c    = 1   ;type 4ch  -  not reg/mem
command4d    = 1   ;type 4dh  -  mul/div a,reg/mem
command4e    = 1   ;type 4eh  -  BOUND-�������� ������� � ��������
command4f    = 1   ;type 4fh  -  ARPL M/R,R -��������� ������. ��. ����������
command50    = 1   ;type 50h  -  ������� �����
command51    = 1   ;type 51h  -  jmp/call far ����.


; ���� ModRM � ���� ����
command61    = 1   ;type 61h  -  mov reg/mem,NOP
command62    = 1   ;type 62h  -  �����. � �����. �������� reg/mem,NOP
command63    = 1   ;type 63h  -  test reg/mem, NOP
command64    = 1   ;type 64h  -  ������
command65    = 1   ;type 65h  -  �������� ��������� reg = reg/mem * NOP


; ������� ������������ � 0F

;1byte-no ModRM,no Data
command81  = 1   ;type81h  -  push/pop sr (fs,gs ONLY)
command82  = 1   ;type82h  -  ����� ����� ���������� ������ TS
command83  = 1   ;type83h  -  bswap ��������� ������� ������ � �����
command84  = 1   ;type84h  -  invd,wbinvd
command85  = 1   ;type85h  -  wrmsr/rdmsr/rdpmc/rdtsc
command86  = 1   ;type86h  -  sysnter/sysexit
command87  = 1   ;type87h  -  cpuid
command88  = 1   ;type88h  -  rsm

;2byte-no Data
commandA1  = 1   ;typeA1h  -  movzx,movsx
commandA2  = 1   ;typeA2h  -  LFS,LGS,..
commandA3  = 1   ;typeA3h  -  �������� �����. R �� R/M
commandA4  = 1   ;typeA4h  -  ����� ������� BS?
commandA5  = 1   ;typeA5h  -  Bit Test R/M,R
commandA6  = 1   ;typeA6h  -  CMPXCHG Reg,R/M
commandA7  = 1   ;typeA7h  -  setxx
commandA8  = 1   ;typeA8h  -  �������� ��� ��������� ;no MODR_M! only REG               ;�� �������, ��� DR4,DR5-����, � CR1,CR4,CR5,CR6,CR7,TR0,TR1,TR2-���
commandA9  = 1   ;typeA9h  -  ����. �����. ��������� ;no MODR_M! only REG
commandAA  = 1   ;typeAAh  -  LAR/LSL
commandAB  = 1   ;typeABh  -  LGDT/SGDT
commandAC  = 1   ;typeACh  -  LIDT/SIDT
commandAD  = 1   ;typeADh  -  LLDT/SLDT
commandAE  = 1   ;typeAEh  -  LMSW/SMSW
commandAF  = 1   ;typeAFh  -  LTR/STR
commandB0  = 1   ;typeB0h  -  VERR/VERW
commandB1  = 1   ;typeB1h  -  CMPXCHG8B
commandB2  = 1   ;typeB2h  -  XADD
commandB3  = 1   ;typeB3h  -  invlpg
commandB4  = 1   ;typeB4h  -  CMOVxx
commandB5  = 1   ;typeB5h  -  ����. ������. ��������� ;no MODR_M! only REG


;1byte-no ModRM
commandC1  = 1   ;typeC1h  -  near jxx


;2byte-all
commandE1  = 1   ;typeE1h  -  SHLD,SHRD
commandE2  = 1   ;BTS/BT/BTR/BTC R/M,NOP