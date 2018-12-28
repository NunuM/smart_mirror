package main

import (
	"encoding/json"
	"fmt"
	"net/http"
	"strings"
)

func main() {
	client := &http.Client{}
	req, _ := http.NewRequest("GET", "https://api.reddit.com/hot.json", nil)
	req.Header.Add("User-Agent", "Smart-Mirror Hot Posts Fetcher by /u/0xffff0000ffff")
	resp, err := client.Do(req)
	if err == nil {
		defer resp.Body.Close()

		decoder := json.NewDecoder(resp.Body)
		var red Reddit
		/*
		bodyBytes, _ := ioutil.ReadAll(resp.Body)
		bodyString := string(bodyBytes)
		fmt.Println(bodyString)
		*/
		if err := decoder.Decode(&red); err != nil {
			fmt.Println("An error ocorred while decoding the json reply" + err.Error())
		} else {
			j, errn := parseToOutReddit(red)
			if errn == nil {
				fmt.Println(j)
			} else {
				fmt.Printf(errn.Error())
			}
		}
	} else {
		fmt.Print("An error ocorred while making the request")
	}
}

func parseToOutReddit(reddit Reddit) (string, error) {
	var out OutRedditSlice
	for _, post := range reddit.Data.Children {
		var data OutReddit
		data.Title = post.Data.Title
		data.Author = "Author: " + post.Data.AuthorFullname
		data.SubReddit = post.Data.SubredditNamePrefixed
		if strings.Contains(post.Data.Thumbnail,"http") {
			data.UrlToImage = post.Data.Thumbnail
		} else {
			data.UrlToImage = ""
		}
		s := fmt.Sprintf("%.0f", post.Data.Ups)
		data.NumberOfUpVotes = "Upvotes: " + s

		out = append(out, data)
	}
	mar, err := json.MarshalIndent(out, "", "   ")
	return string(mar), err
}

type OutReddit struct {
	Title           string `json:"title"`
	UrlToImage      string `json:"urlToImage"`
	SubReddit       string `json:"subreddit"`
	Author          string `json:"author"`
	NumberOfUpVotes string `json:"numberOfUpvotes"`
}

type OutRedditSlice []OutReddit

type Reddit struct {
	Kind string `json:"kind"`
	Data struct {
		Modhash  string `json:"modhash"`
		Dist     int    `json:"dist"`
		Children []struct {
			Kind string `json:"kind"`
			Data struct {
				ApprovedAtUtc              interface{}   `json:"approved_at_utc"`
				Subreddit                  string        `json:"subreddit"`
				Selftext                   string        `json:"selftext"`
				AuthorFullname             string        `json:"author_fullname"`
				Saved                      bool          `json:"saved"`
				ModReasonTitle             interface{}   `json:"mod_reason_title"`
				Gilded                     int           `json:"gilded"`
				Clicked                    bool          `json:"clicked"`
				Title                      string        `json:"title"`
				LinkFlairRichtext          []interface{} `json:"link_flair_richtext"`
				SubredditNamePrefixed      string        `json:"subreddit_name_prefixed"`
				Hidden                     bool          `json:"hidden"`
				Pwls                       int           `json:"pwls"`
				LinkFlairCSSClass          string        `json:"link_flair_css_class"`
				Downs                      int           `json:"downs"`
				ThumbnailHeight            int           `json:"thumbnail_height"`
				HideScore                  bool          `json:"hide_score"`
				Name                       string        `json:"name"`
				Quarantine                 bool          `json:"quarantine"`
				LinkFlairTextColor         string        `json:"link_flair_text_color"`
				AuthorFlairBackgroundColor interface{}   `json:"author_flair_background_color"`
				SubredditType              string        `json:"subreddit_type"`
				Ups                        float64       `json:"ups"`
				Domain                     string        `json:"domain"`
				MediaEmbed                 struct {
				} `json:"media_embed"`
				ThumbnailWidth        int           `json:"thumbnail_width"`
				AuthorFlairTemplateID interface{}   `json:"author_flair_template_id"`
				IsOriginalContent     bool          `json:"is_original_content"`
				UserReports           []interface{} `json:"user_reports"`
				SecureMedia           interface{}   `json:"secure_media"`
				IsRedditMediaDomain   bool          `json:"is_reddit_media_domain"`
				IsMeta                bool          `json:"is_meta"`
				Category              interface{}   `json:"category"`
				SecureMediaEmbed      struct {
				} `json:"secure_media_embed"`
				LinkFlairText       string        `json:"link_flair_text"`
				CanModPost          bool          `json:"can_mod_post"`
				Score               int           `json:"score"`
				ApprovedBy          interface{}   `json:"approved_by"`
				Thumbnail           string        `json:"thumbnail"`
				Edited              interface{}          `json:"edited"`
				AuthorFlairCSSClass interface{}   `json:"author_flair_css_class"`
				AuthorFlairRichtext []interface{} `json:"author_flair_richtext"`
				Gildings            struct {
					Gid1 int `json:"gid_1"`
					Gid2 int `json:"gid_2"`
					Gid3 int `json:"gid_3"`
				} `json:"gildings"`
				PostHint          string      `json:"post_hint"`
				ContentCategories interface{} `json:"content_categories"`
				IsSelf            bool        `json:"is_self"`
				ModNote           interface{} `json:"mod_note"`
				Created           float64     `json:"created"`
				LinkFlairType     string      `json:"link_flair_type"`
				Wls               int         `json:"wls"`
				BannedBy          interface{} `json:"banned_by"`
				AuthorFlairType   string      `json:"author_flair_type"`
				ContestMode       bool        `json:"contest_mode"`
				SelftextHTML      interface{} `json:"selftext_html"`
				Likes             interface{} `json:"likes"`
				SuggestedSort     interface{} `json:"suggested_sort"`
				BannedAtUtc       interface{} `json:"banned_at_utc"`
				ViewCount         interface{} `json:"view_count"`
				Archived          bool        `json:"archived"`
				NoFollow          bool        `json:"no_follow"`
				IsCrosspostable   bool        `json:"is_crosspostable"`
				Pinned            bool        `json:"pinned"`
				Over18            bool        `json:"over_18"`
				Preview           struct {
					Images []struct {
						Source struct {
							URL    string `json:"url"`
							Width  int    `json:"width"`
							Height int    `json:"height"`
						} `json:"source"`
						Resolutions []struct {
							URL    string `json:"url"`
							Width  int    `json:"width"`
							Height int    `json:"height"`
						} `json:"resolutions"`
						Variants struct {
						} `json:"variants"`
						ID string `json:"id"`
					} `json:"images"`
					Enabled bool `json:"enabled"`
				} `json:"preview"`
				MediaOnly                bool          `json:"media_only"`
				LinkFlairTemplateID      interface{}   `json:"link_flair_template_id"`
				CanGild                  bool          `json:"can_gild"`
				Spoiler                  bool          `json:"spoiler"`
				Locked                   bool          `json:"locked"`
				AuthorFlairText          interface{}   `json:"author_flair_text"`
				Visited                  bool          `json:"visited"`
				NumReports               interface{}   `json:"num_reports"`
				Distinguished            interface{}   `json:"distinguished"`
				SubredditID              string        `json:"subreddit_id"`
				ModReasonBy              interface{}   `json:"mod_reason_by"`
				RemovalReason            interface{}   `json:"removal_reason"`
				LinkFlairBackgroundColor string        `json:"link_flair_background_color"`
				ID                       string        `json:"id"`
				IsRobotIndexable         bool          `json:"is_robot_indexable"`
				ReportReasons            interface{}   `json:"report_reasons"`
				Author                   string        `json:"author"`
				NumCrossposts            int           `json:"num_crossposts"`
				NumComments              int           `json:"num_comments"`
				SendReplies              bool          `json:"send_replies"`
				WhitelistStatus          string        `json:"whitelist_status"`
				ModReports               []interface{} `json:"mod_reports"`
				AuthorPatreonFlair       bool          `json:"author_patreon_flair"`
				AuthorFlairTextColor     interface{}   `json:"author_flair_text_color"`
				Permalink                string        `json:"permalink"`
				ParentWhitelistStatus    string        `json:"parent_whitelist_status"`
				Stickied                 bool          `json:"stickied"`
				URL                      string        `json:"url"`
				SubredditSubscribers     int           `json:"subreddit_subscribers"`
				CreatedUtc               float64       `json:"created_utc"`
				Media                    interface{}   `json:"media"`
				IsVideo                  bool          `json:"is_video"`
			} `json:"data"`
		} `json:"children"`
		After  string      `json:"after"`
		Before interface{} `json:"before"`
	} `json:"data"`
}
