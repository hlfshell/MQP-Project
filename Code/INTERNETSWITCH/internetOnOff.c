/**
*
*/

#define GPIODDATA ((void *) 0xE800001C)

int main(){

        int read;

        read = peek16(GPIODDATA);
        read = read << 14;
        read = read & 1;

        if(read == 1){
                system("ln -s -f /etc/init.d/ifupdown-clean /etc/rcS.d/S18ifupdown-clean");
                system("ln -s -f /etc/init.d/pppd-dns /etc/rcS.d/S38pppd-dns");
                system("ln -s -f /etc/init.d/ifupdown /etc/rcS.d/S39ifupdown");
                system("ln -s -f /etc/init.d/networking /etc/rcS.d/S40networking");

                system("ln -s -f /etc/init.d/inetd /etc/rc3.d/S20inetd");
		system("ln -s -f /etc/init.d/ssh /etc/rc3.d/S20ssh");
		system("ln -s -f /etc/init.d/wu-ftpd /etc/rc3.d/S50wu-ftpd");
		system("ln -s -f /etc/init.d/apache2 /etc/rc3.d/S91apache2");
        } else{
		system("rm -f /etc/rcS.d/S18ifupdown-clean");
                system("rm -f /etc/rcS.d/S38pppd-dns");
                system("rm -f /etc/rcS.d/S39ifupdown");
                system("rm -f /etc/rcS.d/S40networking");

                system("rm -f /etc/rc3.d/S20inetd");
                system("rm -f /etc/rc3.d/S20ssh");
                system("rm -f /etc/rc3.d/S50wu-ftpd");
                system("rm -f /etc/rc3.d/S91apache2");
        }

        return 0;
}

