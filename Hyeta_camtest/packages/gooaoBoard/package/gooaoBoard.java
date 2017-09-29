/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-y44
 */
import java.util.*;
import org.mozilla.javascript.*;
import xdc.services.intern.xsr.*;
import xdc.services.spec.Session;

public class gooaoBoard
{
    static final String VERS = "@(#) xdc-y44\n";

    static final Proto.Elm $$T_Bool = Proto.Elm.newBool();
    static final Proto.Elm $$T_Num = Proto.Elm.newNum();
    static final Proto.Elm $$T_Str = Proto.Elm.newStr();
    static final Proto.Elm $$T_Obj = Proto.Elm.newObj();

    static final Proto.Fxn $$T_Met = new Proto.Fxn(null, null, 0, -1, false);
    static final Proto.Map $$T_Map = new Proto.Map($$T_Obj);
    static final Proto.Arr $$T_Vec = new Proto.Arr($$T_Obj);

    static final XScriptO $$DEFAULT = Value.DEFAULT;
    static final Object $$UNDEF = Undefined.instance;

    static final Proto.Obj $$Package = (Proto.Obj)Global.get("$$Package");
    static final Proto.Obj $$Module = (Proto.Obj)Global.get("$$Module");
    static final Proto.Obj $$Instance = (Proto.Obj)Global.get("$$Instance");
    static final Proto.Obj $$Params = (Proto.Obj)Global.get("$$Params");

    static final Object $$objFldGet = Global.get("$$objFldGet");
    static final Object $$objFldSet = Global.get("$$objFldSet");
    static final Object $$proxyGet = Global.get("$$proxyGet");
    static final Object $$proxySet = Global.get("$$proxySet");
    static final Object $$delegGet = Global.get("$$delegGet");
    static final Object $$delegSet = Global.get("$$delegSet");

    Scriptable xdcO;
    Session ses;
    Value.Obj om;

    boolean isROV;
    boolean isCFG;

    Proto.Obj pkgP;
    Value.Obj pkgV;

    ArrayList<Object> imports = new ArrayList<Object>();
    ArrayList<Object> loggables = new ArrayList<Object>();
    ArrayList<Object> mcfgs = new ArrayList<Object>();
    ArrayList<Object> icfgs = new ArrayList<Object>();
    ArrayList<String> inherits = new ArrayList<String>();
    ArrayList<Object> proxies = new ArrayList<Object>();
    ArrayList<Object> sizes = new ArrayList<Object>();
    ArrayList<Object> tdefs = new ArrayList<Object>();

    void $$IMPORTS()
    {
        Global.callFxn("loadPackage", xdcO, "xdc");
        Global.callFxn("loadPackage", xdcO, "xdc.corevers");
        Global.callFxn("loadPackage", xdcO, "ti.platforms.generic");
        Global.callFxn("loadPackage", xdcO, "xdc.platform");
    }

    void $$OBJECTS()
    {
        pkgP = (Proto.Obj)om.bind("gooaoBoard.Package", new Proto.Obj());
        pkgV = (Value.Obj)om.bind("gooaoBoard", new Value.Obj("gooaoBoard", pkgP));
    }

    void Platform$$OBJECTS()
    {
        Proto.Obj po, spo;
        Value.Obj vo;

        po = (Proto.Obj)om.bind("gooaoBoard.Platform.Module", new Proto.Obj());
        vo = (Value.Obj)om.bind("gooaoBoard.Platform", new Value.Obj("gooaoBoard.Platform", po));
        pkgV.bind("Platform", vo);
        // decls 
        om.bind("gooaoBoard.Platform.Board", om.findStrict("xdc.platform.IPlatform.Board", "gooaoBoard"));
        om.bind("gooaoBoard.Platform.Memory", om.findStrict("xdc.platform.IPlatform.Memory", "gooaoBoard"));
        // insts 
        Object insP = om.bind("gooaoBoard.Platform.Instance", new Proto.Obj());
        po = (Proto.Obj)om.bind("gooaoBoard.Platform$$Object", new Proto.Obj());
        Object objP = om.bind("gooaoBoard.Platform.Object", new Proto.Str(po, true));
        po = (Proto.Obj)om.bind("gooaoBoard.Platform$$Params", new Proto.Obj());
        om.bind("gooaoBoard.Platform.Params", new Proto.Str(po, true));
    }

    void Platform$$CONSTS()
    {
        // module Platform
    }

    void Platform$$CREATES()
    {
        Proto.Fxn fxn;
        StringBuilder sb;

        fxn = (Proto.Fxn)om.bind("gooaoBoard.Platform$$create", new Proto.Fxn(om.findStrict("gooaoBoard.Platform.Module", "gooaoBoard"), om.findStrict("gooaoBoard.Platform.Instance", "gooaoBoard"), 3, 2, false));
                fxn.addArg(0, "name", $$T_Str, $$UNDEF);
                fxn.addArg(1, "args", $$T_Obj, $$UNDEF);
                fxn.addArg(2, "__params", (Proto)om.findStrict("gooaoBoard.Platform.Params", "gooaoBoard"), Global.newObject());
        sb = new StringBuilder();
        sb.append("gooaoBoard$Platform$$create = function( name, args, __params ) {\n");
            sb.append("var __mod = xdc.om['gooaoBoard.Platform'];\n");
            sb.append("var __inst = xdc.om['gooaoBoard.Platform.Instance'].$$make();\n");
            sb.append("__inst.$$bind('$package', xdc.om['gooaoBoard']);\n");
            sb.append("__inst.$$bind('$index', __mod.$instances.length);\n");
            sb.append("__inst.$$bind('$category', 'Instance');\n");
            sb.append("__inst.$$bind('$args', {name:name, args:args});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$instances.$add(__inst);\n");
            sb.append("__inst.externalMemoryMap = __mod.PARAMS.externalMemoryMap;\n");
            sb.append("__inst.customMemoryMap = __mod.PARAMS.customMemoryMap;\n");
            sb.append("__inst.renameMap = __mod.PARAMS.renameMap;\n");
            sb.append("__inst.dataMemory = __mod.PARAMS.dataMemory;\n");
            sb.append("__inst.codeMemory = __mod.PARAMS.codeMemory;\n");
            sb.append("__inst.stackMemory = __mod.PARAMS.stackMemory;\n");
            sb.append("__inst.sectMap = __mod.PARAMS.sectMap;\n");
            sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
            sb.append("var save = xdc.om.$curpkg;\n");
            sb.append("xdc.om.$$bind('$curpkg', __mod.$package.$name);\n");
            sb.append("__mod.instance$meta$init.$fxn.apply(__inst, [name, args]);\n");
            sb.append("xdc.om.$$bind('$curpkg', save);\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return __inst;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
        fxn = (Proto.Fxn)om.bind("gooaoBoard.Platform$$construct", new Proto.Fxn(om.findStrict("gooaoBoard.Platform.Module", "gooaoBoard"), null, 4, 2, false));
                fxn.addArg(0, "__obj", (Proto)om.findStrict("gooaoBoard.Platform$$Object", "gooaoBoard"), null);
                fxn.addArg(1, "name", $$T_Str, $$UNDEF);
                fxn.addArg(2, "args", $$T_Obj, $$UNDEF);
                fxn.addArg(3, "__params", (Proto)om.findStrict("gooaoBoard.Platform.Params", "gooaoBoard"), Global.newObject());
        sb = new StringBuilder();
        sb.append("gooaoBoard$Platform$$construct = function( __obj, name, args, __params ) {\n");
            sb.append("var __mod = xdc.om['gooaoBoard.Platform'];\n");
            sb.append("var __inst = __obj;\n");
            sb.append("__inst.$$bind('$args', {name:name, args:args});\n");
            sb.append("__inst.$$bind('$module', __mod);\n");
            sb.append("__mod.$objects.$add(__inst);\n");
            sb.append("__inst.externalMemoryMap = __mod.PARAMS.externalMemoryMap;\n");
            sb.append("__inst.customMemoryMap = __mod.PARAMS.customMemoryMap;\n");
            sb.append("__inst.renameMap = __mod.PARAMS.renameMap;\n");
            sb.append("__inst.dataMemory = __mod.PARAMS.dataMemory;\n");
            sb.append("__inst.codeMemory = __mod.PARAMS.codeMemory;\n");
            sb.append("__inst.stackMemory = __mod.PARAMS.stackMemory;\n");
            sb.append("__inst.sectMap = __mod.PARAMS.sectMap;\n");
            sb.append("for (var __p in __params) __inst[__p] = __params[__p];\n");
            sb.append("__inst.$$bless();\n");
            sb.append("return null;\n");
        sb.append("}\n");
        Global.eval(sb.toString());
    }

    void Platform$$FUNCTIONS()
    {
        Proto.Fxn fxn;

    }

    void Platform$$SIZES()
    {
    }

    void Platform$$TYPES()
    {
        Scriptable cap;
        Proto.Obj po;
        Proto.Str ps;
        Proto.Typedef pt;
        Object fxn;

        cap = (Scriptable)Global.callFxn("loadCapsule", xdcO, "gooaoBoard/Platform.xs");
        om.bind("gooaoBoard.Platform$$capsule", cap);
        po = (Proto.Obj)om.findStrict("gooaoBoard.Platform.Module", "gooaoBoard");
        po.init("gooaoBoard.Platform.Module", om.findStrict("xdc.platform.IPlatform.Module", "gooaoBoard"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("CPU", (Proto)om.findStrict("ti.platforms.generic.Platform.Instance", "gooaoBoard"), $$UNDEF, "wh");
                po.addFxn("create", (Proto.Fxn)om.findStrict("gooaoBoard.Platform$$create", "gooaoBoard"), Global.get("gooaoBoard$Platform$$create"));
                po.addFxn("construct", (Proto.Fxn)om.findStrict("gooaoBoard.Platform$$construct", "gooaoBoard"), Global.get("gooaoBoard$Platform$$construct"));
        fxn = Global.get(cap, "module$use");
        if (fxn != null) om.bind("gooaoBoard.Platform$$module$use", true);
        if (fxn != null) po.addFxn("module$use", $$T_Met, fxn);
        fxn = Global.get(cap, "module$meta$init");
        if (fxn != null) om.bind("gooaoBoard.Platform$$module$meta$init", true);
        if (fxn != null) po.addFxn("module$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "instance$meta$init");
        if (fxn != null) om.bind("gooaoBoard.Platform$$instance$meta$init", true);
        if (fxn != null) po.addFxn("instance$meta$init", $$T_Met, fxn);
        fxn = Global.get(cap, "module$validate");
        if (fxn != null) om.bind("gooaoBoard.Platform$$module$validate", true);
        if (fxn != null) po.addFxn("module$validate", $$T_Met, fxn);
        po = (Proto.Obj)om.findStrict("gooaoBoard.Platform.Instance", "gooaoBoard");
        po.init("gooaoBoard.Platform.Instance", om.findStrict("xdc.platform.IPlatform.Instance", "gooaoBoard"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("codeMemory", $$T_Str, "DDR", "wh");
        po.addFld("dataMemory", $$T_Str, "DDR", "wh");
        po.addFld("stackMemory", $$T_Str, "L3_CBA_RAM", "wh");
                fxn = Global.get(cap, "getCpuDataSheet");
                if (fxn != null) po.addFxn("getCpuDataSheet", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getCpuDataSheet", "gooaoBoard"), fxn);
                fxn = Global.get(cap, "getCreateArgs");
                if (fxn != null) po.addFxn("getCreateArgs", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getCreateArgs", "gooaoBoard"), fxn);
                fxn = Global.get(cap, "getExeContext");
                if (fxn != null) po.addFxn("getExeContext", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getExeContext", "gooaoBoard"), fxn);
                fxn = Global.get(cap, "getExecCmd");
                if (fxn != null) po.addFxn("getExecCmd", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getExecCmd", "gooaoBoard"), fxn);
                fxn = Global.get(cap, "getLinkTemplate");
                if (fxn != null) po.addFxn("getLinkTemplate", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getLinkTemplate", "gooaoBoard"), fxn);
        po = (Proto.Obj)om.findStrict("gooaoBoard.Platform$$Params", "gooaoBoard");
        po.init("gooaoBoard.Platform.Params", om.findStrict("xdc.platform.IPlatform$$Params", "gooaoBoard"));
                po.addFld("$hostonly", $$T_Num, 1, "r");
        po.addFld("codeMemory", $$T_Str, "DDR", "wh");
        po.addFld("dataMemory", $$T_Str, "DDR", "wh");
        po.addFld("stackMemory", $$T_Str, "L3_CBA_RAM", "wh");
        po = (Proto.Obj)om.findStrict("gooaoBoard.Platform$$Object", "gooaoBoard");
        po.init("gooaoBoard.Platform.Object", om.findStrict("gooaoBoard.Platform.Instance", "gooaoBoard"));
                fxn = Global.get(cap, "getCpuDataSheet");
                if (fxn != null) po.addFxn("getCpuDataSheet", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getCpuDataSheet", "gooaoBoard"), fxn);
                fxn = Global.get(cap, "getCreateArgs");
                if (fxn != null) po.addFxn("getCreateArgs", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getCreateArgs", "gooaoBoard"), fxn);
                fxn = Global.get(cap, "getExeContext");
                if (fxn != null) po.addFxn("getExeContext", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getExeContext", "gooaoBoard"), fxn);
                fxn = Global.get(cap, "getExecCmd");
                if (fxn != null) po.addFxn("getExecCmd", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getExecCmd", "gooaoBoard"), fxn);
                fxn = Global.get(cap, "getLinkTemplate");
                if (fxn != null) po.addFxn("getLinkTemplate", (Proto.Fxn)om.findStrict("xdc.platform.IPlatform$$getLinkTemplate", "gooaoBoard"), fxn);
    }

    void Platform$$ROV()
    {
    }

    void $$SINGLETONS()
    {
        pkgP.init("gooaoBoard.Package", (Proto.Obj)om.findStrict("xdc.IPackage.Module", "gooaoBoard"));
        pkgP.bind("$capsule", $$UNDEF);
        pkgV.init2(pkgP, "gooaoBoard", Value.DEFAULT, false);
        pkgV.bind("$name", "gooaoBoard");
        pkgV.bind("$category", "Package");
        pkgV.bind("$$qn", "gooaoBoard.");
        pkgV.bind("$vers", Global.newArray());
        Value.Map atmap = (Value.Map)pkgV.getv("$attr");
        atmap.seal("length");
        imports.clear();
        pkgV.bind("$imports", imports);
        StringBuilder sb = new StringBuilder();
        sb.append("var pkg = xdc.om['gooaoBoard'];\n");
        sb.append("if (pkg.$vers.length >= 3) {\n");
            sb.append("pkg.$vers.push(Packages.xdc.services.global.Vers.getDate(xdc.csd() + '/..'));\n");
        sb.append("}\n");
        sb.append("pkg.build.libraries = [\n");
        sb.append("];\n");
        sb.append("pkg.build.libDesc = [\n");
        sb.append("];\n");
        Global.eval(sb.toString());
    }

    void Platform$$SINGLETONS()
    {
        Proto.Obj po;
        Value.Obj vo;

        vo = (Value.Obj)om.findStrict("gooaoBoard.Platform", "gooaoBoard");
        po = (Proto.Obj)om.findStrict("gooaoBoard.Platform.Module", "gooaoBoard");
        vo.init2(po, "gooaoBoard.Platform", $$DEFAULT, false);
        vo.bind("Module", po);
        vo.bind("$category", "Module");
        vo.bind("$capsule", om.findStrict("gooaoBoard.Platform$$capsule", "gooaoBoard"));
        vo.bind("Instance", om.findStrict("gooaoBoard.Platform.Instance", "gooaoBoard"));
        vo.bind("Params", om.findStrict("gooaoBoard.Platform.Params", "gooaoBoard"));
        vo.bind("PARAMS", ((Proto.Str)om.findStrict("gooaoBoard.Platform.Params", "gooaoBoard")).newInstance());
        vo.bind("$package", om.findStrict("gooaoBoard", "gooaoBoard"));
        tdefs.clear();
        proxies.clear();
        mcfgs.clear();
        icfgs.clear();
        inherits.clear();
        vo.bind("Board", om.findStrict("xdc.platform.IPlatform.Board", "gooaoBoard"));
        tdefs.add(om.findStrict("xdc.platform.IPlatform.Board", "gooaoBoard"));
        vo.bind("Memory", om.findStrict("xdc.platform.IPlatform.Memory", "gooaoBoard"));
        tdefs.add(om.findStrict("xdc.platform.IPlatform.Memory", "gooaoBoard"));
        vo.bind("MemoryMap", om.findStrict("xdc.platform.IPlatform.MemoryMap", "gooaoBoard"));
        vo.bind("$$tdefs", Global.newArray(tdefs.toArray()));
        vo.bind("$$proxies", Global.newArray(proxies.toArray()));
        vo.bind("$$mcfgs", Global.newArray(mcfgs.toArray()));
        vo.bind("$$icfgs", Global.newArray(icfgs.toArray()));
        inherits.add("xdc.platform");
        vo.bind("$$inherits", Global.newArray(inherits.toArray()));
        ((Value.Arr)pkgV.getv("$modules")).add(vo);
        ((Value.Arr)om.findStrict("$modules", "gooaoBoard")).add(vo);
        vo.bind("$$instflag", 1);
        vo.bind("$$iobjflag", 1);
        vo.bind("$$sizeflag", 1);
        vo.bind("$$dlgflag", 0);
        vo.bind("$$iflag", 1);
        vo.bind("$$romcfgs", "|");
        vo.bind("$$nortsflag", 0);
        Proto.Str ps = (Proto.Str)vo.find("Module_State");
        if (ps != null) vo.bind("$object", ps.newInstance());
        vo.bind("$$meta_iobj", om.has("gooaoBoard.Platform$$instance$static$init", null) ? 1 : 0);
        vo.bind("$$fxntab", Global.newArray());
        vo.bind("$$logEvtCfgs", Global.newArray());
        vo.bind("$$errorDescCfgs", Global.newArray());
        vo.bind("$$assertDescCfgs", Global.newArray());
        Value.Map atmap = (Value.Map)vo.getv("$attr");
        atmap.seal("length");
        vo.bind("Object", om.findStrict("gooaoBoard.Platform.Object", "gooaoBoard"));
        pkgV.bind("Platform", vo);
        ((Value.Arr)pkgV.getv("$unitNames")).add("Platform");
    }

    void $$INITIALIZATION()
    {
        Value.Obj vo;

        if (isCFG) {
        }//isCFG
        Global.callFxn("module$meta$init", (Scriptable)om.findStrict("gooaoBoard.Platform", "gooaoBoard"));
        vo = (Value.Obj)om.findStrict("gooaoBoard.Platform", "gooaoBoard");
        Global.put(vo, "CPU", Global.callFxn("create", (Scriptable)om.find("ti.platforms.generic.Platform"), "CPU", Global.newObject("clockRate", 432L, "catalogName", "ti.catalog.c6000", "deviceName", "TMS320C6748", "externalMemoryMap", Global.newArray(new Object[]{Global.newArray(new Object[]{"E_RAM_CS2", Global.newObject("name", "E_RAM_CS2", "base", 0x60000000L, "len", 0x01000000L, "space", "io", "access", "RW")}), Global.newArray(new Object[]{"E_RAM_CS3", Global.newObject("name", "E_RAM_CS3", "base", 0x62000000L, "len", 0x01000000L, "space", "io", "access", "RW")}), Global.newArray(new Object[]{"E_RAM_CS4", Global.newObject("name", "E_RAM_CS4", "base", 0x64000000L, "len", 0x01000000L, "space", "io", "access", "RW")}), Global.newArray(new Object[]{"E_RAM_CS5", Global.newObject("name", "E_RAM_CS5", "base", 0x66000000L, "len", 0x01000000L, "space", "io", "access", "RW")}), Global.newArray(new Object[]{"SN_PAR", Global.newObject("name", "SN_PAR", "base", 0xC0000000L, "len", 0x00180000L, "space", "data", "access", "RW")}), Global.newArray(new Object[]{"DDR2_SN_PAR4", Global.newObject("name", "DDR2_SN_PAR4", "base", 0xC0180000L, "len", 0x00080000L, "space", "data", "access", "RW")}), Global.newArray(new Object[]{"DDR2_RAM", Global.newObject("name", "DDR2_RAM", "base", 0xC0200000L, "len", 0x02D00000L, "space", "data", "access", "RW")}), Global.newArray(new Object[]{"DDR2_USB", Global.newObject("name", "DDR2_USB", "base", 0xC2F00000L, "len", 0x00100000L, "space", "data", "access", "RW")}), Global.newArray(new Object[]{"App_Prog_START", Global.newObject("name", "App_Prog_START", "base", 0xC3000000L, "len", 0x00000400L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"DDR", Global.newObject("name", "DDR", "base", 0xC3000400L, "len", 0x000FF000L, "space", "code/data", "access", "RWX")}), Global.newArray(new Object[]{"Inf1", Global.newObject("name", "Inf1", "base", 0xC30FF400L, "len", 0x00000100L, "space", "data", "access", "RW")}), Global.newArray(new Object[]{"Inf2", Global.newObject("name", "Inf2", "base", 0xC30FF500L, "len", 0x00000100L, "space", "data", "access", "RW")}), Global.newArray(new Object[]{"Inf3", Global.newObject("name", "Inf3", "base", 0xC30FF600L, "len", 0x00000100L, "space", "data", "access", "RW")}), Global.newArray(new Object[]{"Inf4", Global.newObject("name", "Inf4", "base", 0xC30FF700L, "len", 0x00000100L, "space", "data", "access", "RW")}), Global.newArray(new Object[]{"Inf5", Global.newObject("name", "Inf5", "base", 0xC30FF800L, "len", 0x00000800L, "space", "data", "access", "RW")}), Global.newArray(new Object[]{"DDR_EXT", Global.newObject("name", "DDR_EXT", "base", 0xC4000000L, "len", 0x0C000000L, "space", "data", "access", "RW")})}), "l2Mode", "256k", "l1PMode", "32k", "l1DMode", "32k")));
        Global.callFxn("init", pkgV);
        ((Value.Obj)om.getv("gooaoBoard.Platform")).bless();
        ((Value.Arr)om.findStrict("$packages", "gooaoBoard")).add(pkgV);
    }

    public void exec( Scriptable xdcO, Session ses )
    {
        this.xdcO = xdcO;
        this.ses = ses;
        om = (Value.Obj)xdcO.get("om", null);

        Object o = om.geto("$name");
        String s = o instanceof String ? (String)o : null;
        isCFG = s != null && s.equals("cfg");
        isROV = s != null && s.equals("rov");

        $$IMPORTS();
        $$OBJECTS();
        Platform$$OBJECTS();
        Platform$$CONSTS();
        Platform$$CREATES();
        Platform$$FUNCTIONS();
        Platform$$SIZES();
        Platform$$TYPES();
        if (isROV) {
            Platform$$ROV();
        }//isROV
        $$SINGLETONS();
        Platform$$SINGLETONS();
        $$INITIALIZATION();
    }
}
