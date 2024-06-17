#include "gbafe.h"

void SpinRotation_Init(struct ProcSpinRotation * proc)
{
    proc->unk_39 = 0;
    proc->ro = 0;
    proc->unk_35 = 0;
    proc->unk_36 = 0;
    proc->unk_37 = 0;
    proc->unk_38 = 0;
    proc->unk_3A = 0;
    proc->unk_3B = 0;
    proc->unk_3D = 0;
    proc->unk_34 = 0;
}

void SpinRotation_Loop(struct ProcSpinRotation * proc)
{
    proc->ro++;
    proc->angle -= 4;

    /**
     * I don't understand the correspondence between 0x180 and 0x4C.
     */

    BgAffinRoting(BG_2, proc->angle, 0, 0, 0x180, 0x180);
    BgAffinScaling(BG_2, 2 << 8, 1 << 8);
    BgAffinAnchoring(BG_2, 120, 160, 0x4C, 0x4C);

    SyncDispIo();
}

struct ProcCmd CONST_DATA ProcScr_SpinRotation[] = {
    PROC_NAME_DEBUG("SpinRotation"),
    PROC_MARK(13),
    PROC_CALL(SpinRotation_Init),
    PROC_REPEAT(SpinRotation_Loop),
    PROC_END,
};

ProcPtr StartSpinRotation(ProcPtr parent)
{
    struct ProcSpinRotation * proc;
    proc = Proc_Start(ProcScr_SpinRotation, PROC_TREE_VSYNC);
    proc->savedraw = parent;
    return proc;
}
