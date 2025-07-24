import weather from "@/components/weather";
import Calender from "@/components/Calendar";
import request from "@/utils/request";
import home_echarts from "@/components/home_echarts";

export default {
    name: "Home",
    components: {
        weather,
        Calender,
        home_echarts,
    },
    data() {
        return {
            visitorNum: "",
            studentSum: "",
            studentNum: "",
            haveRoomStudentNum: "",
            repairOrderNum: "",
            noFullRoomNum: "",
            detailDialog: false,
            activities: [],
            detail: {},
        };
    },
    created() {
        this.getStuSum();
        this.getHomePageNotice();
        this.getStuNum();
        this.getHaveRoomNum();
        this.getOrderNum();
        this.getNoFullRoom();
        this.getVisitorNum();
    },
    methods: {
        async getStuNum() {
            request.get("/stu/stuNum").then((res) => {
                if (res.code === "0") {
                    this.studentNum = res.data;
                } else {
                    ElMessage({
                        message: res.msg,
                        type: "error",
                    });
                }
            });
        },
        async getStuSum() {
            request.get("/stu/stuSum").then((res) => {
                if (res.code === "0") {
                    this.studentSum = res.data;
                } else {
                    ElMessage({
                        message: res.msg,
                        type: "error",
                    });
                }
            });
        },
        async getVisitorNum() {
            request.get("/visitor/visitorNum").then((res) => {
                if (res.code === "0") {
                    this.visitorNum = res.data;
                } else {
                    ElMessage({
                        message: res.msg,
                        type: "error",
                    });
                }
            });
        },
        async getHaveRoomNum() {
            request.get("/room/selectHaveRoomStuNum").then((res) => {
                if (res.code === "0") {
                    this.haveRoomStudentNum = res.data;
                } else {
                    ElMessage({
                        message: res.msg,
                        type: "error",
                    });
                }
            });
        },
        async getOrderNum() {
            request.get("/repair/orderNum").then((res) => {
                if (res.code === "0") {
                    this.repairOrderNum = res.data;
                } else {
                    ElMessage({
                        message: res.msg,
                        type: "error",
                    });
                }
            });
        },
        async getNoFullRoom() {
            request.get("/room/noFullRoom").then((res) => {
                if (res.code === "0") {
                    this.noFullRoomNum = res.data;
                } else {
                    ElMessage({
                        message: res.msg,
                        type: "error",
                    });
                }
            });
        },
        async getHomePageNotice() {
            request.get("/notice/homePageNotice").then((res) => {
                if (res.code === "0") {
                    this.activities = res.data;
                } else {
                    ElMessage({
                        message: res.msg,
                        type: "error",
                    });
                }
            });
        },
        showDetail(row) {
            this.detailDialog = true;
            this.$nextTick(() => {
                this.detail = row;
            });
        },
        closeDetailDialog() {
            this.detailDialog = false;
        },
    },
};