#include "convert.h"
#include "AESL_pkg.h"

using namespace std;

namespace ap_rtl {

void convert::thread_hdltv_gen() {
    const char* dump_tv = std::getenv("AP_WRITE_TV");
    if (!(dump_tv && string(dump_tv) == "on")) return;

    wait();

    mHdltvinHandle << "[ " << endl;
    mHdltvoutHandle << "[ " << endl;
    int ap_cycleNo = 0;
    while (1) {
        wait();
        const char* mComma = ap_cycleNo == 0 ? " " : ", " ;
        mHdltvinHandle << mComma << "{"  <<  " \"ap_rst\" :  \"" << ap_rst.read() << "\" ";
        mHdltvinHandle << " , " <<  " \"ap_start\" :  \"" << ap_start.read() << "\" ";
        mHdltvoutHandle << mComma << "{"  <<  " \"ap_done\" :  \"" << ap_done.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"ap_idle\" :  \"" << ap_idle.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"ap_ready\" :  \"" << ap_ready.read() << "\" ";
        mHdltvinHandle << " , " <<  " \"width\" :  \"" << width.read() << "\" ";
        mHdltvinHandle << " , " <<  " \"height\" :  \"" << height.read() << "\" ";
        mHdltvinHandle << " , " <<  " \"hp\" :  \"" << hp.read() << "\" ";
        mHdltvinHandle << " , " <<  " \"ht\" :  \"" << ht.read() << "\" ";
        mHdltvinHandle << " , " <<  " \"fw\" :  \"" << fw.read() << "\" ";
        mHdltvinHandle << " , " <<  " \"fh\" :  \"" << fh.read() << "\" ";
        mHdltvinHandle << " , " <<  " \"fovX\" :  \"" << fovX.read() << "\" ";
        mHdltvinHandle << " , " <<  " \"fovY\" :  \"" << fovY.read() << "\" ";
        mHdltvinHandle << " , " <<  " \"option\" :  \"" << option.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"fov_address0\" :  \"" << fov_address0.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"fov_ce0\" :  \"" << fov_ce0.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"fov_we0\" :  \"" << fov_we0.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"fov_d0\" :  \"" << fov_d0.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"fov_address1\" :  \"" << fov_address1.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"fov_ce1\" :  \"" << fov_ce1.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"fov_we1\" :  \"" << fov_we1.read() << "\" ";
        mHdltvoutHandle << " , " <<  " \"fov_d1\" :  \"" << fov_d1.read() << "\" ";
        mHdltvinHandle << "}" << std::endl;
        mHdltvoutHandle << "}" << std::endl;
        ap_cycleNo++;
    }
}

}

