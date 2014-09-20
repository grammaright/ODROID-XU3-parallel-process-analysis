#include "takevalue.h"
#include <QFile>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <QDebug>
Takevalue::Takevalue()
{
    //usage[8] = {0,};
    for (int i = 0; i < 8; i++)
    {
        QString temp;
        temp.sprintf("/sys/devices/system/cpu/cpu%d/cpufreq/cpuinfo_cur_freq", i);
        cpu_node_list[i] = temp;
    }
}
QString Takevalue::GetGPUCurFreq()
{
    FILE *fp = NULL;
    char buf[4] = {'\0',};
    fp = fopen(GPUFREQ_NODE, "r");
    if (fp == NULL)
        {
             return 0;
        }
    fread(buf, 1, 3, fp);
    fclose(fp);
    return buf;
}
QString Takevalue::GetCPUCurFreq(int cpuNum)
{
    FILE *fp = NULL;
    char buf[8] = {'\0',};
    int v;
    fp = fopen(cpu_node_list[cpuNum].toUtf8(), "r");
    if (fp == NULL)
    {
        return 0;
    }
    fread(buf, 1, 8, fp);
    fclose(fp);
    v = atoi(buf) / 1000;
    sprintf(buf, "%d", v);
    return buf;
}
QString Takevalue::GetCPUTemp(int cpuNum)
{
    FILE *fp = NULL;
    fp = fopen(TEMP_NODE, "r");
    char buf[16];
    if (fp == NULL)
    {
        return NULL;
    }
    for (int i = 0; i < cpuNum + 1; i++)
        fread(buf, 1, 16, fp);
    fclose(fp);
    buf[12] = '\0';
    return &buf[9];
}
int Takevalue::open_sensor(const char *node, sensor_t *sensor)
{
    if ((sensor->fd = open(node, O_RDWR)) < 0)
        qDebug() << node << "Open Fail";
    return sensor->fd;
}
int Takevalue::OpenINA231()
{
    if (open_sensor(DEV_SENSOR_ARM, &sensor[SENSOR_ARM]) < 0)
        return -1;
    if (open_sensor(DEV_SENSOR_MEM, &sensor[SENSOR_MEM]) < 0)
        return -1;
    if (open_sensor(DEV_SENSOR_KFC, &sensor[SENSOR_KFC]) < 0)
        return -1;
    if (open_sensor(DEV_SENSOR_G3D, &sensor[SENSOR_G3D]) < 0)
        return -1;
    if (read_sensor_status(&sensor[SENSOR_ARM]))
        return -1;
    if (read_sensor_status(&sensor[SENSOR_MEM]))
        return -1;
    if (read_sensor_status(&sensor[SENSOR_KFC]))
        return -1;
    if (read_sensor_status(&sensor[SENSOR_G3D]))
        return -1;
    if (!sensor[SENSOR_ARM].data.enable)
        enable_sensor(&sensor[SENSOR_ARM], 1);
    if (!sensor[SENSOR_MEM].data.enable)
        enable_sensor(&sensor[SENSOR_MEM], 1);
    if (!sensor[SENSOR_KFC].data.enable)
        enable_sensor(&sensor[SENSOR_KFC], 1);
    if (!sensor[SENSOR_G3D].data.enable)
        enable_sensor(&sensor[SENSOR_G3D], 1);
    return 0;
}
void Takevalue::CloseINA231()
{
    if (sensor[SENSOR_ARM].data.enable)
        enable_sensor(&sensor[SENSOR_ARM], 0);
    if (sensor[SENSOR_MEM].data.enable)
        enable_sensor(&sensor[SENSOR_MEM], 0);
    if (sensor[SENSOR_KFC].data.enable)
        enable_sensor(&sensor[SENSOR_KFC], 0);
    if (sensor[SENSOR_G3D].data.enable)
        enable_sensor(&sensor[SENSOR_G3D], 0);
    close_sensor(&sensor[SENSOR_ARM]);
    close_sensor(&sensor[SENSOR_MEM]);
    close_sensor(&sensor[SENSOR_KFC]);
    close_sensor(&sensor[SENSOR_G3D]);
}
void Takevalue::GetINA231()
{
    read_sensor(&sensor[SENSOR_ARM]);
    read_sensor(&sensor[SENSOR_MEM]);
    read_sensor(&sensor[SENSOR_KFC]);
    read_sensor(&sensor[SENSOR_G3D]);
    armuV = (float)(sensor[SENSOR_ARM].data.cur_uV / 100000) / 10;
    armuA = (float)(sensor[SENSOR_ARM].data.cur_uA / 1000) / 1000;
    armuW = (float)(sensor[SENSOR_ARM].data.cur_uW / 1000) / 1000;
    memuV = (float)(sensor[SENSOR_MEM].data.cur_uV / 100000) / 10;
    memuA = (float)(sensor[SENSOR_MEM].data.cur_uA / 1000) / 1000;
    memuW = (float)(sensor[SENSOR_MEM].data.cur_uW / 1000) / 1000;
    kfcuV = (float)(sensor[SENSOR_KFC].data.cur_uV / 100000) / 10;
    kfcuA = (float)(sensor[SENSOR_KFC].data.cur_uA / 1000) / 1000;
    kfcuW = (float)(sensor[SENSOR_KFC].data.cur_uW / 1000) / 1000;
    g3duV = (float)(sensor[SENSOR_G3D].data.cur_uV / 100000) / 10;
    g3duA = (float)(sensor[SENSOR_G3D].data.cur_uA / 1000) / 1000;
    g3duW = (float)(sensor[SENSOR_G3D].data.cur_uW / 1000) / 1000;
}
void Takevalue::enable_sensor(sensor_t *sensor, unsigned char enable)
{
    if (sensor->fd > 0)
    {
        sensor->data.enable = enable ? 1 : 0;
        if (ioctl(sensor->fd, INA231_IOCSSTATUS, &sensor->data) < 0)
        qDebug() << "IOCTL Error";
    }
}
int Takevalue::read_sensor_status(sensor_t *sensor)
{
    if (sensor->fd > 0)
    {
        if (ioctl(sensor->fd, INA231_IOCGSTATUS, &sensor->data) < 0)
        qDebug() << sensor->data.name << "IOCTL Error";
    }
    return 0;
}
void Takevalue::read_sensor(sensor_t *sensor)
{
    if (sensor->fd > 0)
    {
        if (ioctl(sensor->fd, INA231_IOCGREG, &sensor->data) < 0)
        qDebug() << sensor->data.name << "IOCTL Error!";
    }
}
void Takevalue::close_sensor(sensor_t *sensor)
{
    if (sensor->fd > 0)
    close(sensor->fd);
}
