/*===================== begin_copyright_notice ==================================

Copyright (c) 2017 Intel Corporation

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


======================= end_copyright_notice ==================================*/
#pragma once

#include "GenISAIntrinsics/GenIntrinsicInst.h"

#include "common/LLVMWarningsPush.hpp"
#include <llvm/Pass.h>
#include <llvm/IR/InstVisitor.h>
#include "common/LLVMWarningsPop.hpp"
#include <set>

namespace IGC
{
    class HalfPromotion : public llvm::FunctionPass, public llvm::InstVisitor<HalfPromotion>
    {
    public:
        static char ID;

		HalfPromotion();
        HalfPromotion(bool isOCL);

        virtual llvm::StringRef getPassName() const override
        {
            return "Half Promotion Pass";
        }

        virtual bool runOnFunction(llvm::Function &F) override;
        void visitCallInst(llvm::CallInst &I);
        void visitBinaryOperator(llvm::BinaryOperator &BI);
        void visitFCmp(llvm::FCmpInst &CmpI);
        void visitCastInst(llvm::CastInst &CI);
        void visitPHINode(llvm::PHINode &PHI);
        void visitSelectInst(llvm::SelectInst &SI);

    private:
        void handleGenIntrinsic(llvm::GenIntrinsicInst &I);
        void handleLLVMIntrinsic(llvm::IntrinsicInst &I);

		bool m_isOCL = false;
        bool m_changed = false;
    };

} // namespace IGC
