setfpscap(60)
wait(3)
local httprequest = (syn and syn.request) or http and http.request or http_request or (fluxus and fluxus.request) or request
local httpservice = game:GetService('HttpService')
local function serverHop()
	local gameId = game.PlaceId
	local servers = {}
	local req = httprequest({Url = "https://games.roblox.com/v1/games/"..gameId.."/servers/Public?sortOrder=Desc&excludeFullGames=true&limit=100"})
	local body = httpservice:JSONDecode(req.Body)
	if body and body.data then
		for i, v in next, body.data do
			if type(v) == "table" and tonumber(v.playing) and tonumber(v.maxPlayers) and v.playing < v.maxPlayers and v.playing > v.maxPlayers/1.5 and not (v.id == game.JobId)  then
				table.insert(servers, 1, v.id)
			end 
		end
	end
	if #servers > 0 then
		game:GetService("TeleportService"):TeleportToPlaceInstance(gameId, servers[math.random(1, #servers)], game.Players.LocalPlayer)
	end
	game:GetService("TeleportService").TeleportInitFailed:Connect(function()
		game:GetService("TeleportService"):TeleportToPlaceInstance(gameId, servers[math.random(1, #servers)], game.Players.LocalPlayer)
	end)
end

local function serverRejoin()
	game:GetService("TeleportService"):TeleportToPlaceInstance(game.PlaceId, game.JobId, game.Players.LocalPlayer)
end

local gui = Instance.new("ScreenGui", game.Players.LocalPlayer.PlayerGui)
gui.Name = "GUI"
gui.IgnoreGuiInset = true
gui.DisplayOrder = 999

local top = Instance.new("Frame", gui)
top.Position = UDim2.new(0,0,1,0)
top.Size = UDim2.new(1,0,1,0)
top.BackgroundTransparency = 1
top.LayoutOrder = 3
top.Visible = false

local txt = Instance.new("TextButton", gui)
txt.Name = "textBox"
txt.BackgroundTransparency = 0.5
txt.Size = UDim2.new(0.025, 0, 0.05, 0)
txt.Position = UDim2.new(0.975, 0, 0.95, 0)
txt.TextScaled = true
txt.Font = Enum.Font.FredokaOne
txt.Text = "Hop"
txt.TextColor3 = Color3.new(1, 0.666667, 0)
txt.BackgroundColor3 = Color3.new(1, 1, 0)
txt.LayoutOrder = 1

local txt2 = Instance.new("TextButton", gui)
txt2.Name = "textBox"
txt2.BackgroundTransparency = 0.5
txt2.Size = UDim2.new(0.025, 0, 0.05, 0)
txt2.Position = UDim2.new(0.95, 0, 0.95, 0)
txt2.TextScaled = true
txt2.Font = Enum.Font.FredokaOne
txt2.Text = "Rejoin"
txt2.TextColor3 = Color3.new(1, 0.666667, 0)
txt2.BackgroundColor3 = Color3.new(1, 1, 0)
txt2.LayoutOrder = 1

local colors = {Color3.new(0, 1, 0), Color3.new(0.666667, 1, 0), Color3.new(1, 1, 0), Color3.new(0.333333, 0.666667, 0), Color3.new(0, 0, 1), Color3.new(0.333333, 0, 1), Color3.new(1, 0.333333, 0), Color3.new(1, 0.666667, 0), Color3.new(1, 1, 1)}

txt.MouseButton1Click:Connect(function()
	spawn(serverHop)
	game.StarterGui:SetCoreGuiEnabled(Enum.CoreGuiType.PlayerList, false)
	top.Visible = true
	top.BackgroundColor3 = colors[math.random(1,#colors)]
	game:GetService('TweenService'):Create(top, TweenInfo.new(0.5, Enum.EasingStyle.Sine, Enum.EasingDirection.Out, 0, false, 0), {
		Position = UDim2.new(0, 0, 0, 0)
	}):Play()
	game:GetService('TweenService'):Create(top, TweenInfo.new(0.75, Enum.EasingStyle.Sine, Enum.EasingDirection.Out, 0, false, 0), {
		BackgroundTransparency = 0
	}):Play()
	wait(0.5)
	game:GetService('TweenService'):Create(top, TweenInfo.new(1, Enum.EasingStyle.Sine, Enum.EasingDirection.In, 0, false, 0), {
		BackgroundColor3 = Color3.new(0, 0, 0)
	}):Play()
	wait(30)
	game:GetService('TweenService'):Create(top, TweenInfo.new(0.75, Enum.EasingStyle.Sine, Enum.EasingDirection.In, 0, false, 0), {
		Position = UDim2.new(0,0,1,0)
	}):Play()
	game:GetService('TweenService'):Create(top, TweenInfo.new(0.5, Enum.EasingStyle.Sine, Enum.EasingDirection.In, 0, false, 0), {
		BackgroundTransparency = 1
	}):Play()
end)

txt2.MouseButton1Click:Connect(function()
	spawn(serverRejoin)
	game.StarterGui:SetCoreGuiEnabled(Enum.CoreGuiType.PlayerList, false)
	top.Visible = true
	top.BackgroundColor3 = colors[math.random(1,#colors)]
	game:GetService('TweenService'):Create(top, TweenInfo.new(0.25, Enum.EasingStyle.Sine, Enum.EasingDirection.Out, 0, false, 0), {
		Position = UDim2.new(0, 0, 0, 0)
	}):Play()
	game:GetService('TweenService'):Create(top, TweenInfo.new(0.5, Enum.EasingStyle.Sine, Enum.EasingDirection.Out, 0, false, 0), {
		BackgroundTransparency = 0
	}):Play()
	wait(0.25)
	game:GetService('TweenService'):Create(top, TweenInfo.new(0.5, Enum.EasingStyle.Sine, Enum.EasingDirection.In, 0, false, 0), {
		BackgroundColor3 = Color3.new(0, 0, 0)
	}):Play()
	wait(15)
	game:GetService('TweenService'):Create(top, TweenInfo.new(0.5, Enum.EasingStyle.Sine, Enum.EasingDirection.In, 0, false, 0), {
		Position = UDim2.new(0,0,1,0)
	}):Play()
	game:GetService('TweenService'):Create(top, TweenInfo.new(0.25, Enum.EasingStyle.Sine, Enum.EasingDirection.In, 0, false, 0), {
		BackgroundTransparency = 1
	}):Play()
end)
