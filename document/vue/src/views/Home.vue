<template>
  <el-card style="margin: 15px; min-height: calc(100vh - 80px)">
    <!--    头部数据-->
    <div>
      <el-row :gutter="20" class="topInfo">
        <el-col :span="4">
          <div id="stuSumDiv" class="el-colDiv">
            <div id="ssv3-main-text" class="nowDiv">实时</div>
            <span class="title">学生总数统计</span><br/>
            <span class="digital">{{ this.studentSum }}</span><br/>
            <span class="last-span">当前分类总记录数</span>
          </div>
        </el-col>
        <el-col :span="4">
          <div id="stuNumDiv" class="el-colDiv">
            <div id="ssv1-main-text" class="nowDiv">实时</div>
            <span class="title">在宿学生统计</span><br/>
            <span class="digital">{{ this.studentNum }}</span><br/>
            <span class="last-span">当前分类总记录数</span>
          </div>
        </el-col>
        <el-col :span="4">
          <div id="stuNum1Div" class="el-colDiv">
            <div id="repairNum" class="nowDiv">实时</div>
            <span class="title">访客统计</span><br/>
            <span class="digital">{{ this.visitorNum }}</span><br/>
            <span class="last-span">当前分类总记录数</span>
          </div>
        </el-col>
        <el-col :span="4">
          <div id="haveRoomDiv" class="el-colDiv">
            <div id="ssv2-main-text" class="nowDiv">实时</div>
            <span class="title">住宿人数</span><br/>
            <span class="digital">{{ this.haveRoomStudentNum }}</span><br/>
            <span class="last-span">当前分类总记录数</span>
          </div>
        </el-col>
        <el-col :span="4">
          <div id="repairNum" class="el-colDiv">
            <div id="ssv3-main-text" class="nowDiv">实时</div>
            <span class="title">报修统计</span><br/>
            <span class="digital">{{ this.repairOrderNum }}</span><br/>
            <span class="last-span">当前分类总记录数</span>
          </div>
        </el-col>
        <el-col :span="4">
          <div id="emptyRoom" class="el-colDiv">
            <div id="ssv4-main-text" class="nowDiv">实时</div>
            <span class="title">空宿舍统计</span><br/>
            <span class="digital">{{ this.noFullRoomNum }}</span><br/>
            <span class="last-span">当前分类总记录数</span>
          </div>
        </el-col>
      </el-row>
    </div>
    <!-- 下部-->
    <div style="display: flex;width: 100%;margin-top: 40px;align-items: center;justify-content: center;">
      <!--   左侧 宿舍通告-->
      <div style="margin-right: 5%">
        <span style="font-size: 22px;display: block;margin-bottom: 30px;margin-left: 10px;">宿舍通告</span>
        <el-timeline>
          <el-timeline-item
              v-for="(activity, index) in activities"
              :key="index"
              :timestamp="activity.releaseTime"
              @click.native="showDetail(activity)"
          >
                        <span class="notice-title" :class="'priority-' + activity.priority">
                            <i :class="activity.icon"></i> {{ activity.title }}
                        </span>
          </el-timeline-item>
        </el-timeline>
      </div>
      <el-dialog v-model="detailDialog" title="详情" width="50%">
        <el-card>
          <div v-html="detail.content"></div>npm
        </el-card>
        <template #footer>
              <span class="dialog-footer">
                <el-button type="primary" @click="closeDetailDialog">确 定</el-button>
              </span>
        </template>
      </el-dialog>
      <!--   中部-->
      <div style="height: 588px">
        <span style="
            font-size: 22px;
            display: block;
            margin-bottom: 30px;
            margin-left: 10px;
          ">宿舍学生人数分布图</span>
        <home_echarts/>
      </div>
      <!--  右侧-->
      <div style="margin-left: 5%">
        <!--   天气组件-->
        <weather/>
        <!--    日历组件-->
        <el-card style="width: 380px; max-height: 440px; margin-top: 17px">
          <Calender/>
        </el-card>
      </div>
    </div>
  </el-card>
</template>
<script src="@/assets/js/Home.js"></script>
<style scoped>@import '../assets/css/Home.css';</style>