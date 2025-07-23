#include <QApplication>
#include <QLabel>
#include <QString>
#include <rclcpp/rclcpp.hpp>
#include <status_interfaces/msg/system_status.hpp>

using SystemStatus = status_interfaces::msg::SystemStatus;

class SysStatusDisplay : public rclcpp::Node
{
private:
    rclcpp::Subscription<SystemStatus>::SharedPtr subscriber_;
    QLabel *label_;
public:
    SysStatusDisplay() : Node("sys_status_display")
    {
        label_ = new QLabel();
        subscriber_ = this->create_subscription<SystemStatus>("sys_status", 10, [&]
        (const SystemStatus::SharedPtr msg) -> void {
            label_->setText(get_qstr_from_msg(msg));
        });
        label_->setText(get_qstr_from_msg(
            std::make_shared<SystemStatus>()
        ));
        label_->show();
    }

    QString get_qstr_from_msg(const SystemStatus::SharedPtr msg)
    {
        std::stringstream show_str;
        show_str << "----------Table of Current System Status----------\n" 
                 << "time:\t" << msg->stamp.sec << "\ts\n" 
                 << "host name:\t" << msg->host_name << "\t\n" 
                 << "cpu percent:\t" << msg->cpu_percent << "\t%\n" 
                 << "memory percent:\t" << msg->memory_percent << "\t%\n" 
                 << "memory total:\t" << msg->memory_total << "\tMB\n" 
                 << "memory available:\t" << msg->memory_available << "\tMB\n" 
                 << "net sent:\t" << msg->net_sent << "\tMB\n" 
                 << "net recv:\t" << msg->net_recv << "\tMB\n";
        return QString::fromStdString(show_str.str());
    };
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    QApplication app(argc, argv);
    auto node = std::make_shared<SysStatusDisplay>();

    std::thread spin_thread([&]() -> void{
        rclcpp::spin(node);
    });
    spin_thread.detach();
    app.exec();
    return 0;
}