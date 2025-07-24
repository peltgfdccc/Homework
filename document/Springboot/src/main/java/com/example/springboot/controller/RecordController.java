package com.example.springboot.controller;


import com.baomidou.mybatisplus.extension.plugins.pagination.Page;
import com.example.springboot.common.Result;
import com.example.springboot.entity.Record;
import com.example.springboot.entity.Repair;
import com.example.springboot.service.AdminService;
import com.example.springboot.service.RecordService;
import org.springframework.web.bind.annotation.*;

import javax.annotation.Resource;

@RestController
@RequestMapping("/record")
public class RecordController {

    @Resource
    private RecordService recordService;

    @PostMapping("/add")
    public Result<?> add(@RequestBody Record record) {
        int i = recordService.addRecord(record);
        if (i == 1) {
            return Result.success();
        } else {
            return Result.error("-1", "添加失败");
        }
    }
    /**
     * 访客删除
     */
    @DeleteMapping("/delete/{id}")
    public Result<?> delete(@PathVariable Integer id) {
        int i = recordService.deleteRecord(id);
        if (i == 1) {
            return Result.success();
        } else {
            return Result.error("-1", "删除失败");
        }
    }

    /**
     * 访客查询
     */
    @GetMapping("/find")
    public Result<?> findPage(@RequestParam(defaultValue = "1") Integer pageNum,
                              @RequestParam(defaultValue = "10") Integer pageSize,
                              @RequestParam(defaultValue = "") String search) {
        Page page = recordService.find(pageNum, pageSize, search);
        if (page != null) {
            return Result.success(page);
        } else {
            return Result.error("-1", "查询失败");
        }
    }
}
