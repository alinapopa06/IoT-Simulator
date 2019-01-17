#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <gtk/gtk.h>
#include <stdlib.h>
#include <gtk/gtk.h>

extern int errno;
int sd, continue_timer = 0, start_timer =0, sec_expired = 100;

GtkWidget* create_window (char *file1,char *file2)
{
   GError* error = NULL;
   GtkWidget *window;
   GtkBuilder *builder;

   builder = gtk_builder_new ();
   if (!gtk_builder_add_from_file (builder, file1, &error))
   {
      g_error_free (error);
   }

   gtk_builder_connect_signals (builder, NULL);
   window = GTK_WIDGET (gtk_builder_get_object (builder, file2));
   if (NULL == window)
   {
      fprintf(stderr, "Unable to file object with id \"interfata\" \n");
      return window;
   }
}

int bec(GtkWindow *window)
{
    int port;
    char buf[10],ip[100];
    GtkWidget *secondWindow;
    struct sockaddr_in server; 

    printf("%s\n","Ati ales dispozitivul: bec." );
    printf("%s\n", "Puteti inchide becul sau schimba luminozitatea.");
    gtk_window_close(window);
    secondWindow = create_window("bec1.glade", "bec");
    gtk_widget_show_all(secondWindow); 

    strcpy(ip,"127.0.0.1");
    strcpy(buf,"2907");
    port=atoi(buf);

    if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
      {
        perror ("Eroare la socket().\n");
        return errno;
      }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_port = htons (port);
  
    if (connect (sd, (struct sockaddr *) &server,sizeof (struct sockaddr)) == -1)
      {
        perror ("[client]Eroare la connect().\n");
        return errno;
      }
}

void updateLabel(GtkLabel *label, int nr)
{
    gchar *display;
    display = g_strdup_printf("%d", nr);         //nr to str
    gtk_label_set_text (GTK_LABEL(label), display); //label to display
}

void minus_bec(GtkButton *button, GtkLabel *label)
{
    char buff[20];
    strcpy(buff,"minus");
    write(sd, buff, 20);
    int nr = atoi(gtk_label_get_text(label));

    if (write (sd,&nr,sizeof(int)) <= 0)
      {
        perror ("[client]Eroare la write() spre server.\n");
      }

	read(sd,&nr,sizeof(int));

    updateLabel(GTK_LABEL(label), nr);
}

void plus_bec(GtkButton *button, GtkLabel *label)
{
    char buff[20];
    strcpy(buff,"plus");
    write(sd, buff, 20);
    int nr = atoi(gtk_label_get_text(label));

    if (write (sd,&nr,sizeof(int)) <= 0)
    {
      perror ("[client]Eroare la write() spre server.\n");
    }

    read(sd,&nr,sizeof(int));

    updateLabel(GTK_LABEL(label), nr);
}

void on_off_bec(GtkSwitch *sw)
{
    char buff[20]="S-a inchis becul";

    if(gtk_switch_get_active(sw)!=0)
      { 
        if (write (sd,buff,20) <= 0)
        perror ("[client]Eroare la write() spre server.\n");
        gtk_main_quit();
      }
}

int tv(GtkWindow *window)
{
    int port;
    GtkWidget *secondWindow;
    struct sockaddr_in server;
    char buf[10],ip[100];

    printf("%s\n","Se utilizeaza dispozitivul: telecomanda TV" );
    printf("%s\n","Puteti schimba canalul sau volumul");
    
    gtk_window_close(window);
    secondWindow = create_window("telecomanda.glade", "telecomanda");
    gtk_widget_show_all(secondWindow);  

    strcpy(ip,"127.0.0.1");
    strcpy(buf, "2908");
    port=atoi(buf);

    if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
      {
        perror ("Eroare la socket().\n");
        return errno;
      }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_port = htons (port);
  
    if (connect (sd, (struct sockaddr *) &server,sizeof (struct sockaddr)) == -1)
     {
        perror ("[client]Eroare la connect().\n");
        return errno;
     }
}

void on_off_telecomanda(GtkSwitch *sw)
{
    char buff[30]="S-a inchis telecomanda";

    if(gtk_switch_get_active(sw)!=0)
      { 
        if (write (sd,buff,30) <= 0)
        perror ("[client]Eroare la write() spre server.\n");
        gtk_main_quit();
      }
}

void c0(GtkButton *button, GtkLabel *label)
{ 
    char buff[30];
    strcpy(buff,"0");
    write(sd, buff, 30);
    int nr = 0;

    if (write (sd,&nr,sizeof(int)) <= 0)
      {
        perror ("[client]Eroare la write() spre server.\n");
      }

    updateLabel(GTK_LABEL(label), nr);
}

void c1(GtkButton *button, GtkLabel *label)
{
    char buff[30];
    strcpy(buff,"1");
    write(sd, buff, 30);
    int nr = 1;

    if (write (sd,&nr,sizeof(int)) <= 0)
      {
        perror ("[client]Eroare la write() spre server.\n");
      }

    updateLabel(GTK_LABEL(label), nr);
}

void c2(GtkButton *button, GtkLabel *label)
{  
    char buff[30];
    strcpy(buff,"2");
    write(sd, buff, 30);
    int nr = 2;

    if (write (sd,&nr,sizeof(int)) <= 0)
      {
        perror ("[client]Eroare la write() spre server.\n");
      }

    updateLabel(GTK_LABEL(label), nr);;
}

void c3(GtkButton *button, GtkLabel *label)
{
    int nr=3; 
    char buff[30];
    strcpy(buff,"3");
    write(sd, buff, 30);

    if (write (sd,&nr,sizeof(int)) <= 0)
      {
        perror ("[client]Eroare la write() spre server.\n");
      }

    updateLabel(GTK_LABEL(label), nr);
}

void c4(GtkButton *button, GtkLabel *label)
{
    int nr=4; 
    char buff[30];
    strcpy(buff,"4");
    write(sd, buff, 30);

    if (write (sd,&nr,sizeof(int)) <= 0)
      {
        perror ("[client]Eroare la write() spre server.\n");
      }

    updateLabel(GTK_LABEL(label), nr);
}

void c5(GtkButton *button, GtkLabel *label)
{
   int nr=5; 
    char buff[30];
    strcpy(buff,"5");
    write(sd, buff, 30);

    if (write (sd,&nr,sizeof(int)) <= 0)
      {
        perror ("[client]Eroare la write() spre server.\n");
      }

    updateLabel(GTK_LABEL(label), nr);
}

void c6(GtkButton *button, GtkLabel *label)
{
    int nr=6;
    char buff[30];
    strcpy(buff,"6");
    write(sd, buff, 30);

    if (write (sd,&nr,sizeof(int)) <= 0)
      {
        perror ("[client]Eroare la write() spre server.\n");
      }

    updateLabel(GTK_LABEL(label), nr);
}

void c7(GtkButton *button, GtkLabel *label)
{
    int nr=7;
    char buff[30];
    strcpy(buff,"7");
    write(sd, buff, 30);

    if (write (sd,&nr,sizeof(int)) <= 0)
      {
        perror ("[client]Eroare la write() spre server.\n");
      }

    updateLabel(GTK_LABEL(label), nr);
}

void c8(GtkButton *button, GtkLabel *label)
{
    int nr=8;
    char buff[30];
    strcpy(buff,"8");
    write(sd, buff, 30);

    if (write (sd,&nr,sizeof(int)) <= 0)
      {
        perror ("[client]Eroare la write() spre server.\n");
      }
    updateLabel(GTK_LABEL(label), nr);
}

void c9(GtkButton *button, GtkLabel *label)
{
    int nr=9; 
    char buff[30];
    strcpy(buff,"9");
    write(sd, buff, 30);

    if (write (sd,&nr,sizeof(int)) <= 0)
      {
        perror ("[client]Eroare la write() spre server.\n");
      }
    updateLabel(GTK_LABEL(label), nr);
}

void cok()
{   
    char buff[30];

    strcpy(buff,"OK");
    if (write (sd,buff,30) <= 0)
    {
      perror ("[client]Eroare la write() spre server.\n");
    }
}

void minus_telecomanda (GtkButton *button, GtkLabel *label)
{
    char buff[30];
    int nr = atoi(gtk_label_get_text(label));

    strcpy(buff,"minus");
    write(sd, buff, 30);
   
    if (write (sd,&nr,sizeof(int)) <= 0)
        perror ("[client]Eroare la write() spre server.\n");

    read(sd,&nr,sizeof(int));
  
    updateLabel(GTK_LABEL(label), nr);
}

void plus_telecomanda (GtkButton *button, GtkLabel *label)
{
    char buff[30];
    int nr = atoi(gtk_label_get_text(label));

    strcpy(buff,"plus");
    write(sd, buff, 30);

    if (write (sd,&nr,sizeof(int)) <= 0)
      perror ("[client]Eroare la write() spre server.\n");

    read(sd,&nr,sizeof(int));

    updateLabel(GTK_LABEL(label), nr);
}

void jos_telecomanda (GtkButton *button, GtkLabel *label)
{
    char buff[30];
    int nr = atoi(gtk_label_get_text(label));

    strcpy(buff,"jos");
    write(sd, buff, 30);

    if (write (sd,&nr,sizeof(int)) <= 0)
      perror ("[client]Eroare la write() spre server.\n");

    read(sd,&nr,sizeof(int));

    updateLabel(GTK_LABEL(label), nr);
}

void sus_telecomanda (GtkButton *button, GtkLabel *label)
{
    char buff[30];
    int nr = atoi(gtk_label_get_text(label));

    strcpy(buff,"sus");
    write(sd, buff, 30);

    if (write (sd,&nr,sizeof(int)) <= 0)
      perror ("[client]Eroare la write() spre server.\n");

    read(sd,&nr,sizeof(int));

    updateLabel(GTK_LABEL(label), nr);
}

int timer(GtkWindow *window)
{
    int port;
    struct sockaddr_in server;  
    char buf[10],ip[100];

    printf("%s\n","Ati ales dispozitivul: timer" );
    gtk_window_close(window);
    GtkWidget *secondWindow;
    secondWindow = create_window("timer.glade", "timer");
    gtk_widget_show_all(secondWindow);  

    strcpy(ip,"127.0.0.1");
    strcpy(buf, "2909");
    port=atoi(buf);
  
    if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
      {
        perror ("Eroare la socket().\n");
        return errno;
      }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_port = htons (port);

    if (connect (sd, (struct sockaddr *) &server,sizeof (struct sockaddr)) == -1)
      {
        perror ("[client]Eroare la connect().\n");
        return errno;
      }
}


static gboolean label_update(gpointer data)
{
    GtkLabel *label = (GtkLabel*)data;
    char buf[256];
    memset(&buf, 0, 256);
    snprintf(buf, 255, "%d", sec_expired--);
    write(sd,buf,256);
    gtk_label_set_label(label, buf);
    return continue_timer;
}

void start (GtkWidget *button, gpointer data)
{
    GtkWidget *label = data;
    if(start_timer==0)
    {
        g_timeout_add_seconds(1, label_update, label);
        start_timer=1;
        char a[2];
        a[0]=start_timer+'0';
        a[1]='\n';
        write(sd, a,2);
        continue_timer = 1;
    }
}

void stop (GtkWidget *button, gpointer data)
{
    if(start_timer==1)
    {
        GtkWidget *label = data;
        continue_timer = !continue_timer;
        if(continue_timer==1)
        {
            g_timeout_add_seconds(1, label_update, label);
        }
    
    }
}

void reset (GtkWidget *button, gpointer data)
{    
    GtkLabel *label = (GtkLabel*)data;
    sec_expired = 100;
    updateLabel(label,100);
    continue_timer = 0;
    start_timer = 0;
}

int main(int argc, char *argv[])
{
    GtkWidget *window;
    gtk_init(&argc, &argv);
    window = create_window("interfata.glade", "interfata");
    printf("%s\n", "Alegeti unul dintre cele 3 dispozitive.");
    gtk_widget_show_all(window);
    gtk_main();
}
