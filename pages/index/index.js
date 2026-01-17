// index.js
const appData = getApp();
console.log(appData);
console.log(appData.globalData.url);
Page({
  data: {
    //motto: "Hello World",
    url:appData.globalData.url,
    swiperDataArr:[],
    indexCourseFreeData:[],
    indexCourseDiscountData:[],
    indexCourseBoutiqueData:[],
  },
  onLoad(){
    this.getSwiperData();
    this.getIndexCourseList("free","1","5");
    this.getIndexCourseList("discount","1","6");
    this.getIndexCourseList("boutique","1","7");
  },
  //获取后台轮播图数据
  getSwiperData(){
    console.log("获取轮播图数据");
    wx.request({
      url: `${this.data.url}/weChat/applet/course/banner/list?number=5`,
      //data:
      //header:
      method:"GET",
      success:(res)=>{
        console.log(res);
        if(res.data.code==0){
          this.setData({
            swiperDataArr:res.data.data
          })
          console.log(this.data.swiperDataArr);
        }else{
          wx.showToast({
            title: '请求失败',
            icon:"error"
          })
        }
      }
    })
  },
  getIndexCourseList(type,pageNum,pageSize){
    console.log("获取后台课程列表数据");
    wx.request({
      url: `${this.data.url}/weChat/applet/course/list/type`,
      method:"post",
      header:{
        "content-type":"application/x-www-form-urlencoded"
      },
      data:{
        type,
        pageNum,
        pageSize
      },
      success:(res)=>{
        //console.log(res);
        if (res.data.code==0) {
          if (type=="free") {
            this.setData({
              indexCourseFreeData: res.data.rows
            }) 
          }
          if (type=="discount") {
            this.setData({
              indexCourseDiscountData: res.data.rows
            }) 
          }
          if (type=="boutique") {
            this.setData({
              indexCourseBoutiqueData: res.data.rows
            }) 
          }
          console.log(this.data.indexCourseFreeData);
          console.log(this.data.indexCourseDiscountData);
          console.log(this.data.indexCourseBoutiqueData);
        }else{
          wx.showToast({
            title: '暂无数据',
            icon:"error"
          })
        }
      }
    })
  },
  jumpSearchPage(){
    wx.switchTab({
      url: '/pages/search/search',
    })
  }

})
