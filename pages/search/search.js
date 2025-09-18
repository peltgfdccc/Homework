// pages/search/search.js
const appData = getApp();
Page({

  /**
   * 页面的初始数据
   */
  data: {
    url:appData.globalData.url,
    searchDataList:[],
  },

  /**
   * 生命周期函数--监听页面加载
   */
  valueFn(event){
    console.log(event);
    console.log(event.detail.value);
    this.getSearchResultData(event.detail.value);
  },
  getSearchResultData(value){
    wx.request({
      url: `${this.data.url}/pc/course/search/keyword?pageNum=1&pageSize=10&keyword=${value}`,
      method:"GET",
      success:(res)=>{
        console.log(res);
        if (res.data.code==0) {
          if (res.data.total>0) {
            this.setData({
              searchDataList:res.data.courseList
            })
          }else{
            wx.showToast({
              title: '没有该课程',
              icon:"error"
            })
          }
        } else {
          wx.showToast({
            title: '请求失败',
            icon:"error"
          })
          
        }
      }
    })
  },
   onLoad(options) {

  }
})