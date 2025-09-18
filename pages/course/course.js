// pages/course/course.js

const appData = getApp();
console.log(appData);
console.log(appData.globalData.url);
Page({

  /**
   * 页面的初始数据
   */
  data: {
    active: 1,
    url:appData.globalData.url
  },

  /**
   * 生命周期函数--监听页面加载
   */
  onLoad(options) {
    this.getSubjustList();
  },
  onChange(event) {
    wx.showToast({
      title: `切换到标签 ${event.detail.name}`,
      icon: 'none',
      subjectCourseData:[]
    });
  },
  getSubjustList(){
    var data_1 = {
      enable:1
    };
    wx.request({
      url: `${this.data.url}/weChat/applet/subject/list`,
      method:"POST",
      data: JSON.stringify(data_1),
      header:{
        "Content-Type":"application/json"
      },
      success:(res)=>{
        console.log(res);
        if (res.data.code==0) {
          this.setData({
            subjectCourseData:res.data.rows
          })
        } else {
          wx.showToast({
            title: '暂无数据',
            icon:"error"
          })
        }
      }
    })
  }


})