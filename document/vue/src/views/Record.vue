<template>
    <div>
      <el-breadcrumb separator-icon="ArrowRight" style="margin: 16px">
        <el-breadcrumb-item :to="{ path: '/home' }">首页</el-breadcrumb-item>
        <el-breadcrumb-item>离校返校登记</el-breadcrumb-item>
      </el-breadcrumb>
      <el-card style="margin: 15px; min-height: calc(100vh - 111px)">
        <el-button type="primary" @click="openDialog">新增登记</el-button>
        <el-table :data="tableData" style="width: 100%">
          <!-- <el-table-column prop="id" label="ID" width="180"></el-table-column> -->
          <el-table-column prop="studentName" label="学生姓名" width="180"></el-table-column>
          <el-table-column prop="goDate" label="离校/返校日期"></el-table-column>
          <el-table-column prop="type" label="类型" :formatter="formatType"></el-table-column>
          <el-table-column label="操作">
            <template #default="scope">
              <!-- <el-button size="mini" @click="editRow(scope.row)">编辑</el-button> -->
              <el-button size="mini" type="danger" @click="deleteRow(scope.row)">删除</el-button>
            </template>
          </el-table-column>
        </el-table>
        <!-- 弹窗 -->
        <el-dialog :title="dialogTitle" v-model="dialogVisible" width="30%">
          <el-form :model="form" :rules="rules" ref="formRef" label-width="120px">
            <!-- <el-form-item label="ID" prop="id">
              <el-input v-model="form.id" disabled></el-input>
            </el-form-item> -->
            <el-form-item label="学生姓名" prop="studentName">
              <el-input v-model="form.studentName"></el-input>
            </el-form-item>
            <el-form-item label="离校/返校日期" prop="goDate">
              <el-date-picker v-model="form.goDate" type="date" placeholder="选择日期"></el-date-picker>
            </el-form-item>
            <el-form-item label="类型" prop="type">
              <el-select v-model="form.type" placeholder="请选择">
                <el-option label="离校" value="leave"></el-option>
                <el-option label="返校" value="return"></el-option>
              </el-select>
            </el-form-item>
          </el-form>
          <template #footer>
            <span class="dialog-footer">
              <el-button @click="dialogVisible = false">取消</el-button>
              <el-button type="primary" @click="saveForm">确定</el-button>
            </span>
          </template>
        </el-dialog>
      </el-card>
    </div>
  </template>
  
  <script>
  import request from "@/utils/request";
  const {ElMessage} = require("element-plus");
  export default {
    data() {
      return {
        dialogVisible: false,
        dialogTitle: '新增登记',
        tableData: [],
        form: {
          id: '',
          studentName: '',
          goDate: '',
          type: ''
        },
        rules: {
          studentName: [
            { required: true, message: '请输入学生姓名', trigger: 'blur' }
          ],
          goDate: [
            { required: true, message: '请选择日期', trigger: 'change' }
          ],
          type: [
            { required: true, message: '请选择类型', trigger: 'change' }
          ]
        }
      };
    },
    created() {
        this.load();
        this.loading = true;
        setTimeout(() => {
            //设置延迟执行
            this.loading = false;
        }, 1000);
    },
    methods: {
        async load() {
            request.get("/record/find", {
                params: {
                    pageNum: this.currentPage,
                    pageSize: this.pageSize,
                    search: this.search,
                },
            }).then((res) => {
                console.log(res);
                this.tableData = res.data.records;
                this.total = res.data.total;
                this.loading = false;
            });
        },
      openDialog() {
        console.log("触发---")
        this.dialogVisible = true;
        this.dialogTitle = '新增登记';
        this.resetForm();
      },
      editRow(row) {
        this.dialogVisible = true;
        this.dialogTitle = '编辑登记';
        this.form = { ...row };
      },
      async saveForm() {
        const formattedDate = this.formatDate(this.form.goDate);
      this.form.goDate = formattedDate; // 更新 form.goDate 为格式化后的字符
      this.$refs.formRef.validate((valid) => {
        if (valid) {
          request.post("/record/add", this.form)
            .then((res) => {
              if (res.code === "0") {
                ElMessage({
                  message: "新增成功",
                  type: "success",
                });
                this.search = "";
                this.loading = true;
                this.load()
                this.dialogVisible = false;
              } else {
                ElMessage({
                  message: "新增失败：" + res.message,
                  type: "error",
                });
              }
            })
            .catch((error) => {
              ElMessage({
                message: "请求失败：" + error.message,
                type: "error",
              });
            });
        } else {
          ElMessage({
            message: "请检查输入",
            type: "warning",
          });
          return false;
        }
      });
    },
    formatDate(date) {
  const options = { year: 'numeric', month: '2-digit', day: '2-digit' };
  return new Intl.DateTimeFormat('zh-CN', options).format(date);
},
      deleteRow(row) {
        const index = this.tableData.findIndex((item) => item.id === row.id);
        request.delete("/record/delete/" + row.id).then((res) => {
                if (res.code === "0") {
                    ElMessage({
                        message: "删除成功",
                        type: "success",
                    });
                    this.search = "";
                    this.load();
                } else {
                    ElMessage({
                        message: res.msg,
                        type: "error",
                    });
                }
            });
        
        if (index !== -1) {
          this.tableData.splice(index, 1);
        }
      },
      resetForm() {
        if (this.$refs.formRef) {
          this.$refs.formRef.resetFields();
        }
      },
      formatType(row, column) {
        return row.type === 'leave' ? '离校' : '返校';
      }
    }
  };
  </script>
  
  <style scoped>
  /* 在这里添加CSS样式 */
  </style>